#include <iostream>

#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QFrame>
#include <QFile>

#include <widgetzeug/ColorSchemePresetsWidget.h>
#include <widgetzeug/ColorGradientWidget.h>

#include "libzeug-version.h"

using namespace widgetzeug;


ColorSchemePresetsWidget * getOrCreateColorSchemePresetsWidget()
{
    static ColorSchemePresetsWidget * widget{ nullptr };

    if (widget)
        return widget;

    widget = ColorSchemePresetsWidget::fromJson("data/colorbrewer.json");
    return widget;
}

ColorGradientWidget * getOrCreateColorGradientWidget(QLabel * label)
{
    static ColorGradientWidget * widget{ nullptr };

    if (widget)
        return widget;

    const auto gradient = ColorGradient::fromList(
        { { 252, 15, 38 },{ 255, 251, 180 },{ 21, 134, 191 } } , ColorGradientType::Discrete, 10);

    const QList<uint> histogram { 21,14,10,22,42,58,130,227,377,540,816,1424,1674,2172,2453,2533,2515,2285,2337,2761,2896,2702,2495,2508,2641,2686,2845,2982,2984,3171,3301,3335,3380,3436,3378,3396,3544,3622,3695,3745,3842,3751,3710,3763,3779,3702,3840,3920,3807,3663,3724,3663,3537,3450,3506,3335,3158,3165,3137,3073,3120,3005,3009,3060,3017,3029,2908,2980,2848,2789,2819,2788,2783,2803,2738,2813,2647,2715,2704,2735,2660,2752,2882,2796,2977,2751,2786,2730,2582,2827,2728,2795,2722,2634,2440,2544,2408,2500,2510,2552,2474,2470,2454,2617,2738,2867,3045,3163,3351,3169,3343,3361,3701,4008,4296,4027,3864,3703,3681,3763,3770,3828,3988,3757,3769,3897,3824,3668,3666,3718,3894,3808,4109,3987,3946,3889,4007,3923,3711,3672,3642,3645,3476,3319,3463,3388,3284,3453,3478,3694,4008,3963,4079,3932,3833,3756,3462,3061,2692,2579,2345,2172,1874,1754,1844,1897,1982,1899,1903,2018,2067,2099,1961,2069,2222,2219,2152,2061,1931,1927,1879,1787,1850,1822,1857,1913,1863,2015,2035,2026,1896,1905,1940,1951,1850,1756,1792,1715,1699,1621,1613,1644,1577,1608,1682,1851,1808,1690,1526,1432,1354,1271,1103,1031,957,815,783,633,614,503,445,350,320,281,278,244,252,196,184,181,179,152,150,142,130,127,114,123,121,102,96,103,109,94,88,110,81,103,91,97,62,80,82,69,131,597 };

    widget = new ColorGradientWidget{ gradient };
    widget->setHistogram(histogram);

    QObject::connect(widget, &QDialog::accepted,
        [label]()
        {
            auto image = widget->gradient().image(label->width());
            label->setPixmap(QPixmap::fromImage(image));
        });

    return widget;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("widgetzeug-example");
    QApplication::setOrganizationName(META_AUTHOR_ORGANIZATION);
    QApplication::setApplicationVersion(META_VERSION);
    
    QWidget mainWidget;

    auto schemeButton = new QPushButton{ "Choose Scheme Widget" };

    QObject::connect(schemeButton, &QPushButton::pressed,
        []() {  getOrCreateColorSchemePresetsWidget()->show(); });

    auto hline = new QFrame;
    hline->setFrameShape(QFrame::HLine);
    hline->setFrameShadow(QFrame::Sunken);

    auto gradientButton = new QPushButton{ "Color Gradient Widget" };

    auto label = new QLabel{ &mainWidget };
    label->setScaledContents(true);
    label->setMinimumHeight(32);    

    QObject::connect(gradientButton, &QPushButton::pressed,
        [label] () {  getOrCreateColorGradientWidget(label)->show(); });

    auto layout = new QVBoxLayout{ &mainWidget };
    layout->addWidget(schemeButton);
    layout->addWidget(hline);
    layout->addWidget(gradientButton);
    layout->addWidget(label);

    mainWidget.show();

    auto result = app.exec();
    return result;
}
