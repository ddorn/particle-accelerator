//
// Created by diego on 3/18/19.
//

#ifndef PARTICLEACCELERATOR_QTSUPPORT_H
#define PARTICLEACCELERATOR_QTSUPPORT_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include <QOpenGLFunctions>
#include "Support.h"
#include "GlSphere.h"
#include "all.h"
#include "themes.h"
#include "vertex_shader.h"


enum ViewMode {
    FREE_VIEW,
    FIRST_PERSON,
    THIRD_PERSON,
    TOP_VIEW
};

typedef std::vector<std::unique_ptr<Theme>> ThemeVector;

class QtSupport : public Support, protected QOpenGLFunctions {
private:
    // GPU communication
    QOpenGLShaderProgram prog;
    GLSphere sphere;
    GLuint epflTexture;
    // Camera
    QMatrix4x4 view;
    ViewMode viewMode;
    Vector3D position;
    particle_ptr followedParticle;
    bool viewInsideAccelerator_ = false;
    // Themes
    ThemeVector themes;
    size_t themeIndex = 0;
public:
    // Initialisation
    QtSupport() : viewMode(FREE_VIEW) {};
    void init();
    void initPosition();
    void initThemes();
    
    void setViewMode(ViewMode v) { viewMode = v; }
    void nextTheme(int n = 1);
    const Theme* theme() const { return themes[themeIndex].get(); }
    const QMatrix4x4 updateViewMatrix(const Accelerator &accelerator);
    void saveView(const Accelerator& accelerator) { view = updateViewMatrix(accelerator); }


    // Draw objects

    void drawCube(const QMatrix4x4 &model);
    void drawCube(const Vector3D &pos, double scale);
    void drawSphere(const QMatrix4x4 &model, const Color &color);
    void drawSphere(const Vector3D &pos, double scale, const Color &color);
    void drawCircle(const QMatrix4x4 &model, double r=1, double g=1, double b=1, size_t points=30);
    void drawCircle(const Vector3D &pos, double radius, const Vector3D &dir, const Color &color);
    void drawVector(const Vector3D &vec, const Vector3D &start = Vector3D());
    void drawTube(const Vector3D &start, const Vector3D &end, double radius, const Color &color);
    void drawCurvedTube(const Vector3D &start, const Vector3D &end, const Vector3D &center, double radius,
                        const Color &color);


    void draw(const Accelerator &accelerator) override;
    void draw(const CurvedElement &element) override;
    void draw(const Quadrupole &quadrupole) override;
    void draw(const StraightElement &element) override;
    void draw(const Vector3D &d) override;
    void draw(const Particle &particle) override;
    void draw(const Element &element) override;
    void draw(const Dipole &) override;
    void draw(const Sextupole &) override;
    void draw(const Beam &) override {};

    void drawParticles(const Accelerator &accelerator);
    void drawElements(const Accelerator &accelerator);

    // Set view
    void setProjection(const QMatrix4x4 &projection)
    { prog.setUniformValue("projection", projection); }
    void translate(double x, double y, double z);
    void rotate(double angle, double dir_x, double dir_y, double dir_z);
    QMatrix4x4 lookAt(const Vector3D &eyePosition, const Vector3D &center, const Vector3D &up);
    void draw(const Segment &element) override;

private:
    /**
     * Convert a position and a scale to the corresponding matrix
     * @param pos Position of the object
     * @param scale Scale of the object
     * @return
     */
    QMatrix4x4 posToModel(const Vector3D &pos, double scale);
    /**
     * Whether the eye is forced inside the accelerator by the ViewMode.
     */
    bool viewInsideAccelerator() { return viewInsideAccelerator_; }

    /**
     * Whether Elements drawn should be lit or not
     */
    bool elementsLighting() { return theme()->isElementFilled() && !viewInsideAccelerator(); }
    void sendPoint(const Vector3D &point) { prog.setAttributeValue(VertexId, point.x(), point.y(), point.z()); };
    void sendNormal(const Vector3D &normal = Vector3D(2, 2, 4)) { glNormal3f(normal.x(), normal.y(), normal.z()); }
    void sendColor(const Color &color) { prog.setAttributeValue(ColorId, color.r(), color.g(), color.b(), color.a()); }
    void sendColor(double r, double g, double b, double a = 1) { prog.setAttributeValue(ColorId, r, g, b, a); }

};


#endif //PARTICLEACCELERATOR_QTSUPPORT_H
