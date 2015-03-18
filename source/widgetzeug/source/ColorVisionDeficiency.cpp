#include <widgetzeug/ColorVisionDeficiency.h>

#include <cmath>

#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>


namespace widgetzeug
{

QColor daltonize(const QColor & color, ColorVisionDeficiency deficiency)
{
    // http://www.daltonize.org/2010/05/there-is-not-just-one-color-blindness.html
    // http://www.color-blindness.com/2007/01/23/confusion-lines-of-the-cie-1931-color-space/
    // http://jfly.iam.u-tokyo.ac.jp/color

    struct CIEDeficiency
    {
        CIEDeficiency() { }
        CIEDeficiency(const QVector2D & dcp, const QVector2D & begin, const QVector2D & end)
        : dcp(dcp), begin(begin), end(end)
        {
            clm  = (end[1] - begin[1]) / (end[0] - begin[0]);
            clyi = begin[1] - begin[0] * clm;
        }

        QVector2D dcp;  // dichromatic convergence points
        QVector2D begin;
        QVector2D end;
        float     clm;
        float     clyi; // "y-intercept" of axis (actually on the v-axis)
    };


    /* The following algorithm is based on: http://colorlab.wickline.org/colorblind/colorlab/

        The color_blind_sims() JavaScript function in the is copyright(c) 2000-2001
        by Matthew Wickline and the Human-Computer Interaction Resource Network (http://hcirn.com)
    */

    static const auto gamma = 2.2f;

    // D65 white point xyz coords http://en.wikipedia.org/wiki/Standard_illuminant
    static const QVector3D D65(0.312713f, 0.329016f, 0.358271f);

    // sRGB to/from XYZ for D65 http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
    static const auto XYZ = QMatrix4x4 {    // converts sRGB to XYZ
         0.4124564f,  0.3575761f,  0.1804375f,  0.f,
         0.2126729f,  0.7151522f,  0.0721750f,  0.f,
         0.0193339f,  0.1191920f,  0.9503041f,  0.f,
         0.0000000f,  0.0000000f,  0.0000000f,  1.f };
    static const auto RGB = QMatrix4x4{    // converts XYZ to sRGB
         3.2404542f, -1.5371385f, -0.4985314f,  0.f,
        -0.9692660f,  1.8760108f,  0.0415560f,  0.f,
         0.0556434f, -0.2040259f,  1.0572252f,  0.f,
         0.0000000f,  0.0000000f,  0.0000000f,  1.f };

    CIEDeficiency CIED;
    switch (deficiency)
    {
    case ColorVisionDeficiency::Protanope:
        CIED = CIEDeficiency({ 0.735f, 0.265f }, { 0.115807f, 0.073581f }, { 0.471899f, 0.527051f });
        break;
    case ColorVisionDeficiency::Deuteranope:
        CIED = CIEDeficiency({ 1.14f, -0.14f },  { 0.102776f, 0.102864f }, { 0.505845f, 0.493211f });
        break;
    case ColorVisionDeficiency::Tritanope:
        CIED = CIEDeficiency({ 0.171f, -0.003f }, { 0.045391f, 0.294976f }, { 0.665764f, 0.334011f });
        break;
    case ColorVisionDeficiency::Grayscale:
        {
            const auto gray = float{ qGray(color.rgb()) / 255.f };
            return QColor::fromRgbF(gray, gray, gray, color.alphaF());
        }
    case ColorVisionDeficiency::None:
    default:
        return color;
    };

    const auto crgb = QVector3D(pow(color.redF(), gamma), pow(color.greenF(), gamma), pow(color.blueF(), gamma));

    auto cxyz = QVector3D{ XYZ * crgb };
    const auto csum = 1.f / (cxyz[0] + cxyz[1] + cxyz[2]);

    const auto cuvY = QVector3D{ cxyz[0] * csum, cxyz[1] * csum, 0.f };

    // find neutral grey at this luminosity
    auto nxyz = QVector3D{ D65[0], 0.f, D65[2] };
    nxyz *= cxyz[1] / D65[1];

    // retrieve confusion line between color and the deficiency confusion point
    float clm;
    if (cuvY[0] < CIED.dcp[0])
        clm = (CIED.dcp[1] - cuvY[1]) / (CIED.dcp[0] - cuvY[0]);
    else
        clm = (cuvY[1] - CIED.dcp[1]) / (cuvY[0] - CIED.dcp[0]);

    const auto clyi = cuvY[1] - cuvY[0] * clm;

    // find the change in the u and v dimensions (no Y change)
    auto duvY = QVector3D{ 0.f, 0.f, 0.f };
    duvY[0] = (CIED.clyi - clyi) / (clm - CIED.clm);
    duvY[1] = (clm * duvY[0]) + clyi;

    // find the simulated color's XYZ coords
    const auto sxyz = QVector3D{ duvY[0] * cxyz[1] / duvY[1], cxyz[1], (1.f - (duvY[0] + duvY[1])) * cxyz[1] / duvY[1] };
    auto srgb = RGB * sxyz;

    // note the RGB differences between sim color and our neutral color
    const auto drgb = RGB * QVector3D(nxyz[0] - sxyz[0], 0.f, nxyz[2] - sxyz[2]);

    // find out how much to shift sim color toward neutral to fit in RGB space
    QVector3D argb;
    argb[0] = drgb[0] ? ((srgb[0] < 0 ? 0.f : 1.f) - srgb[0]) / drgb[0] : 0.f;
    argb[0] = drgb[1] ? ((srgb[1] < 0 ? 0.f : 1.f) - srgb[1]) / drgb[1] : 0.f;
    argb[0] = drgb[2] ? ((srgb[2] < 0 ? 0.f : 1.f) - srgb[2]) / drgb[2] : 0.f;

    const auto adjust = qMax<float>(qMax<float>(
        (argb[0] > 1.f || argb[0] < 0.f) ? 0.f : argb[0],
        (argb[1] > 1.f || argb[1] < 0.f) ? 0.f : argb[1]),
        (argb[2] > 1.f || argb[2] < 0.f) ? 0.f : argb[2]);

    // now shift *all* three proportional to the greatest shift...
    srgb += adjust * drgb;

    srgb[0] = pow(qBound<float>(0.f, srgb[0], 1.f), 1.f / gamma);
    srgb[1] = pow(qBound<float>(0.f, srgb[1], 1.f), 1.f / gamma);
    srgb[2] = pow(qBound<float>(0.f, srgb[2], 1.f), 1.f / gamma);

    return QColor::fromRgbF(srgb[0], srgb[1], srgb[2], color.alphaF());
}

} // namespace widgetzeug
