#pragma once


#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtGui/QColor>
#include <propertyzeug/propertyzeug.h>


namespace propertyzeug {


/**
*  @brief
*    Empty class to implement file name attributes
*/
class FileName : public QString {
    public:
        FileName() : QString() {}
        FileName(const QString &string) : QString(string) {}
};


/**
*  @brief
*    Empty class to implement texture attributes
*/
class Texture : public QString {
    public:
        Texture() : QString() {}
        Texture(const QString &string) : QString(string) {}
};


/**
*  @brief
*    Attribute base class
*/
class AttributeBase : public QObject {
	public:
		enum Type {
			TypeUnknown,
			TypeString,
			TypeBool,
			TypeInt,
			TypeUnsignedInt,
			TypeLong,
			TypeUnsignedLong,
			TypeChar,
			TypeUnsignedChar,
			TypeFloat,
			TypeDouble,
			TypeColor,
            TypeColorMap,
            TypeFileName,
            TypeTexture
		};


	public:
		AttributeBase(Type type, const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : m_type(type), m_name(name), m_title(title), m_obj(obj), m_getFunc(getFunc), m_setFunc(setFunc) { }
		virtual ~AttributeBase() { }
		Type    getType()  const { return m_type;  }
		QString getName()  const { return m_name;  }
		QString getTitle() const { return m_title; }
		void    setTitle(const QString &title) { m_title = title; }


	protected:
		Type     m_type;
		QString  m_name;
		QString  m_title;
		QObject *m_obj;
		QString  m_getFunc;
		QString  m_setFunc;
};

/**
*  @brief
*    Generic attribute class
*/
template <typename T>
class Attribute : public AttributeBase {
	public:
		static T NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeUnknown, name, title, obj, getFunc, setFunc) { }
		~Attribute() { }
};


/**
*  @brief
*    String attribute
*/
template <>
class Attribute<QString> : public AttributeBase {
	public:
		static QString NullValue() { return QString(); }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeString, name, title, obj, getFunc, setFunc), m_editable(false) { }
		~Attribute() { }
		QString getValue() const { QString value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(QString, value)); return value; }
		void setValue(const QString &value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(QString, value)); }
		bool isEditable() const { return m_editable; }
		void setEditable(bool editable) { m_editable = editable; }
		bool hasChoices() const { return !m_choices.isEmpty(); }
		const QStringList &getChoices() const { return m_choices; }
		void clearChoices() { m_choices.clear(); }
		void setChoices(const QStringList &choices) { m_choices = choices; }
		void addChoice(const QString &value) { m_choices.append(value); }

	private:
		QStringList m_choices;
		bool        m_editable;
};


/**
*  @brief
*    Boolean attribute
*/
template <>
class Attribute<bool> : public AttributeBase {
	public:
		static bool NullValue() { return false; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeBool, name, title, obj, getFunc, setFunc) { }
		~Attribute() { }
		bool getValue() const { bool value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(bool, value)); return value; }
		void setValue(bool value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(bool, value)); }
};


/**
*  @brief
*    Integer attribute
*/
template <>
class Attribute<int> : public AttributeBase {
	public:
		static int NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeInt, name, title, obj, getFunc, setFunc), m_tracking(true), m_min(0), m_max(0) { }
		~Attribute() { }
		int getValue() const { int value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(int, value)); return value; }
		void setValue(int value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(int, value)); }
		int getMinValue() const { return m_min; }
		void setMinValue(int min) { m_min = min; }
		int getMaxValue() const { return m_max; }
		void setMaxValue(int max) { m_max = max; }
		bool getTracking() const { return m_tracking; }
		void setTracking(bool tracking) { m_tracking = tracking; }

	private:
		bool m_tracking;
		int m_min;
		int m_max;
};


/**
*  @brief
*    Long attribute
*/
template <>
class Attribute<long> : public AttributeBase {
	public:
		static long NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeLong, name, title, obj, getFunc, setFunc), m_tracking(true), m_min(0), m_max(0) { }
		~Attribute() { }
		long getValue() const { long value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(long, value)); return value; }
		void setValue(long value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(long, value)); }
		long getMinValue() const { return m_min; }
		void setMinValue(long min) { m_min = min; }
		long getMaxValue() const { return m_max; }
		void setMaxValue(long max) { m_max = max; }
		bool getTracking() const { return m_tracking; }
		void setTracking(bool tracking) { m_tracking = tracking; }

	private:
		bool m_tracking;
		long m_min;
		long m_max;
};


/**
*  @brief
*    Unsigned integer attribute
*/
template <>
class Attribute<unsigned int> : public AttributeBase {
	public:
		static unsigned int NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeUnsignedInt, name, title, obj, getFunc, setFunc), m_tracking(true), m_min(0), m_max(0) { }
		~Attribute() { }
		unsigned int getValue() const { unsigned int value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned int, value)); return value; }
		void setValue(unsigned int value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(unsigned int, value)); }
		unsigned int getMinValue() const { return m_min; }
		void setMinValue(unsigned int min) { m_min = min; }
		unsigned int getMaxValue() const { return m_max; }
		void setMaxValue(unsigned int max) { m_max = max; }
		bool getTracking() const { return m_tracking; }
		void setTracking(bool tracking) { m_tracking = tracking; }

	private:
		bool m_tracking;
		unsigned int m_min;
		unsigned int m_max;
};


/**
*  @brief
*    Unsigned long attribute
*/
template <>
class Attribute<unsigned long> : public AttributeBase {
	public:
		static unsigned long NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeUnsignedLong, name, title, obj, getFunc, setFunc), m_tracking(true), m_min(0), m_max(0) { }
		~Attribute() { }
		unsigned long getValue() const { unsigned long value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned long, value)); return value; }
		void setValue(unsigned long value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(unsigned long, value)); }
		unsigned long getMinValue() const { return m_min; }
		void setMinValue(unsigned long min) { m_min = min; }
		unsigned long getMaxValue() const { return m_max; }
		void setMaxValue(unsigned long max) { m_max = max; }
		bool getTracking() const { return m_tracking; }
		void setTracking(bool tracking) { m_tracking = tracking; }

	private:
		bool m_tracking;
		unsigned long m_min;
		unsigned long m_max;
};


/**
*  @brief
*    Char attribute
*/
template <>
class Attribute<char> : public AttributeBase {
	public:
		static char NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeChar, name, title, obj, getFunc, setFunc), m_tracking(true), m_min(0), m_max(0) { }
		~Attribute() { }
		char getValue() const { char value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(char, value)); return value; }
		void setValue(char value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(char, value)); }
		char getMinValue() const { return m_min; }
		void setMinValue(char min) { m_min = min; }
		char getMaxValue() const { return m_max; }
		void setMaxValue(char max) { m_max = max; }
		bool getTracking() const { return m_tracking; }
		void setTracking(bool tracking) { m_tracking = tracking; }

	private:
		bool m_tracking;
		char m_min;
		char m_max;
};


/**
*  @brief
*    Unsigned char attribute
*/
template <>
class Attribute<unsigned char> : public AttributeBase {
	public:
		static unsigned char NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeUnsignedChar, name, title, obj, getFunc, setFunc), m_tracking(true), m_min(0), m_max(0) { }
		~Attribute() { }
		unsigned char getValue() const { unsigned char value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(unsigned char, value)); return value; }
		void setValue(unsigned char value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(unsigned char, value)); }
		unsigned char getMinValue() const { return m_min; }
		void setMinValue(unsigned char min) { m_min = min; }
		unsigned char getMaxValue() const { return m_max; }
		void setMaxValue(unsigned char max) { m_max = max; }
		bool getTracking() const { return m_tracking; }
		void setTracking(bool tracking) { m_tracking = tracking; }

	private:
		bool m_tracking;
		unsigned char m_min;
		unsigned char m_max;
};


/**
*  @brief
*    Float attribute
*/
template <>
class Attribute<float> : public AttributeBase {
	public:
		static float NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeFloat, name, title, obj, getFunc, setFunc), m_tracking(true), m_min(0.0f), m_max(0.0f) { }
		~Attribute() { }
		float getValue() const { float value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(float, value)); return value; }
		void setValue(float value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(float, value)); }
		float getMinValue() const { return m_min; }
		void setMinValue(float min) { m_min = min; }
		float getMaxValue() const { return m_max; }
		void setMaxValue(float max) { m_max = max; }
		bool getTracking() const { return m_tracking; }
		void setTracking(bool tracking) { m_tracking = tracking; }

	private:
		bool m_tracking;
		float m_min;
		float m_max;
};


/**
*  @brief
*    Double attribute
*/
template <>
class Attribute<double> : public AttributeBase {
	public:
		static double NullValue() { return 0; }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeDouble, name, title, obj, getFunc, setFunc), m_tracking(true), m_min(0.0), m_max(0.0) { }
		~Attribute() { }
		double getValue() const { double value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(double, value)); return value; }
		void setValue(double value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(double, value)); }
		double getMinValue() const { return m_min; }
		void setMinValue(double min) { m_min = min; }
		double getMaxValue() const { return m_max; }
		void setMaxValue(double max) { m_max = max; }
		bool getTracking() const { return m_tracking; }
		void setTracking(bool tracking) { m_tracking = tracking; }

	private:
		bool m_tracking;
		double m_min;
		double m_max;
};


/**
*  @brief
*    Color attribute
*/
template <>
class Attribute<QColor> : public AttributeBase {
	public:
		static QColor NullValue() { return QColor(); }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeColor, name, title, obj, getFunc, setFunc) { }
		~Attribute() { }
		QColor getValue() const { QColor value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(QColor, value)); return value; }
		void setValue(const QColor &value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(QColor, value)); }
};


/**
*  @brief
*    Color attribute
*/
/*
template <>
class Attribute<ColorMap> : public AttributeBase {
	public:
		static ColorMap NullValue() { return ColorMap(); }

	public:
		Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeColorMap, name, title, obj, getFunc, setFunc) { }
		~Attribute() { }
		ColorMap getValue() const { ColorMap value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(ColorMap, value)); return value; }
		void setValue(const ColorMap &value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(ColorMap, value)); }
};
*/

/**
*  @brief
*    Filename attribute
*/
template <>
class Attribute<FileName> : public AttributeBase {
    public:
        static FileName NullValue() { return FileName(); }

    public:
        Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeFileName, name, title, obj, getFunc, setFunc) { }
        ~Attribute() { }
        FileName getValue() const { FileName value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(FileName, value)); return value; }
        void setValue(const FileName &value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(FileName, value)); }
};

/**
*  @brief
*    Texture filename attribute
*/
template <>
class Attribute<Texture> : public AttributeBase {
    public:
        static Texture NullValue() { return Texture(); }

    public:
        Attribute(const QString &name, const QString &title, QObject *obj, const QString &getFunc, const QString &setFunc) : AttributeBase(TypeTexture, name, title, obj, getFunc, setFunc) { }
        ~Attribute() { }
        Texture getValue() const { Texture value; QMetaObject::invokeMethod(m_obj, m_getFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_RETURN_ARG(Texture, value)); return value; }
        void setValue(const Texture &value) { QMetaObject::invokeMethod(m_obj, m_setFunc.toLocal8Bit().data(), Qt::DirectConnection, Q_ARG(Texture, value)); }
        QStringList getFiles() const { return m_files; }
        void setFiles(const QStringList &files) { m_files = files; }

    private:
        QStringList m_files;
};


} // namespace
