
import os
import sys
import shutil

directory = os.path.join(sys.argv[1], 'propertyInstanciationTests')
generatedCppsFile = sys.argv[2]

# 
datatypes = ['bool', 'int8_t', 'uint8_t', 'int16_t', 'uint16_t', 'int32_t', 'uint32_t', 'int64_t', 'uint64_t']


def getSpecificFileContent(datatype, datatypeC):
    content = '''
#include <gmock/gmock.h>

#include <string>

#include <reflectionzeug/property/Property.h>

#include "../MyObject.h"

using namespace reflectionzeug;



class PropertyInstance${CAPITALDATATYPE}_test : public testing::Test
{
public:
    PropertyInstance${CAPITALDATATYPE}_test()
    {
    }

protected:
};


// Propterty instanciaton (read/write)

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};
    auto set = [] (const ${DATATYPE} & val) {};

    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", get, set);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::constgetterconst, &MyObject<${DATATYPE}>::setterconst);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::getterconst, &MyObject<${DATATYPE}>::setterconst);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciatePropertyWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::getterconst, &MyObject<${DATATYPE}>::setter);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton (read only)

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstPropertyWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};

    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", get);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstPropertyWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::constgetterconst);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstPropertyWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", obj, &MyObject<${DATATYPE}>::getterconst);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}



// Propterty instanciaton with Accessor (read/write)

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String)
{
    auto accessor = new AccessorValue<${DATATYPE}>();
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<${DATATYPE}>(0);
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};
    auto set = [] (const ${DATATYPE} & val) {};
    auto accessor = new AccessorGetSet<${DATATYPE}>(get, set);

    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<${DATATYPE}>(obj, &MyObject<${DATATYPE}>::constgetterconst, &MyObject<${DATATYPE}>::setterconst);
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<${DATATYPE}>(obj, &MyObject<${DATATYPE}>::getterconst, &MyObject<${DATATYPE}>::setterconst);
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateAccessorWith_String_Object_GetterConst_Setter)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<${DATATYPE}>(obj, &MyObject<${DATATYPE}>::getterconst, &MyObject<${DATATYPE}>::setter);
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}


// Propterty instanciaton with Accessor (read only)

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String)
{
    auto accessor = new AccessorValue<const ${DATATYPE}>();
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_Value)
{
    auto accessor = new AccessorValue<const ${DATATYPE}>(0);
    auto prop = new Property<${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_LambdaGetter_LambdaSetter)
{
    auto get = [] () {return 0;};
    auto accessor = new AccessorGetSet<const ${DATATYPE}>(get);

    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());

    delete prop;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_Object_ConstGetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<const ${DATATYPE}>(obj, &MyObject<${DATATYPE}>::constgetterconst);
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}

TEST_F(PropertyInstance${CAPITALDATATYPE}_test, instanciateConstAccessorWith_String_Object_GetterConst_SetterConst)
{
    auto obj = new MyObject<${DATATYPE}>;
    auto accessor = new AccessorGetSet<const ${DATATYPE}>(obj, &MyObject<${DATATYPE}>::getterconst);
    auto prop = new Property<const ${DATATYPE}>("${DATATYPE}Property", accessor);

    ASSERT_EQ(typeid(${DATATYPE}), prop->type());


    delete prop;
    delete obj;
}
'''
    content = content.replace('${DATATYPE}', datatype)
    content = content.replace('${CAPITALDATATYPE}', datatypeC)
    return content

def generateInstanciationTest(filepath, datatype, datatypeC):
    content = getSpecificFileContent(datatype, datatypeC)
    with open(filepath, 'wb') as f:
        f.write(content)

print 'Generating reflectionzeug property instanciation tests.'

if os.path.exists(directory):
    shutil.rmtree(directory)
os.mkdir(directory)

with open(generatedCppsFile, 'wb') as f:
    for datatype in datatypes:
        datatypeC = datatype.title()
        filepath = os.path.join(directory, 'PropertyInstanciation' + datatypeC + '_test.cpp')
        generateInstanciationTest(filepath, datatype, datatypeC)
        filename = '/'.join(filepath.split('/')[-2:])
        f.write(filename)
        f.write("\n")

print 'Generation of reflectionzeug property instanciation tests done!'
