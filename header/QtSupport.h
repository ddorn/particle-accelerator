//
// Created by diego on 3/18/19.
//

#ifndef PARTICLEACCELERATOR_QTSUPPORT_H
#define PARTICLEACCELERATOR_QTSUPPORT_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
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

class QtSupport : public Support {
private:
    QOpenGLShaderProgram prog;
    QMatrix4x4 view; // Camera
    GLSphere sphere;
    ViewMode viewMode;
    ThemeVector themes;
    size_t themeIndex = 0;
public:
    // Initialisation
    // TODO: Why not put those two in the constructor ? Isn't it its purpose ?
    // Answer: because it simply doesn't work... but why ?
    void init();
    void initPosition();
    void initThemes();
    void setViewMode(ViewMode v) { viewMode = v; }
    void nextTheme() { themeIndex += 1; themeIndex %= themes.size(); }
    const Theme* theme() const { return themes[themeIndex].get(); }
    const QMatrix4x4 updateViewMatrix(const Accelerator &accelerator);
    void saveView(const Accelerator& accelerator) { view = updateViewMatrix(accelerator); }


    // Draw objects

    void drawCube(const QMatrix4x4 &model);
    void drawCube(const Vector3D &position, double scale);
    void drawSphere(const QMatrix4x4 &model, double r = 1, double g = 1, double b = 1);
    void drawSphere(const QMatrix4x4 &model, const Vector3D &color);
    void drawSphere(const Vector3D& position, double scale, const Vector3D &color);
    void drawSphere(const Vector3D& position, double scale, double r = 1, double g = 1, double b = 1);
    void drawCircle(const QMatrix4x4 &model, double r=1, double g=1, double b=1, size_t points=30);
    void drawCircle(const Vector3D &position, double radius, const Vector3D &dir, const Vector3D &color);
    void drawVector(const Vector3D &vec, const Vector3D &start = Vector3D());
    void drawTube(const QMatrix4x4 &model, double radius, const Vector3D &color, double length);
    void drawTube(const Vector3D& start, const Vector3D& end, double radius, const Vector3D& color = Vector3D(0.2, 0.6, 1));
    void drawCurvedTube(const Vector3D &start, const Vector3D &end, const Vector3D &center, double radius, const Vector3D &color);


    void draw(const Accelerator &accelerator) override;
    void draw(const CurvedElement &element) override;
    void draw(const Quadrupole &quadrupole) override;
    void draw(const StraightElement &element) override;
    void draw(const Vector3D &d) override;
    void draw(const Particle &particle) override;
    void draw(const Element &element) override;
    void draw(const Dipole &) override;
    void draw(const Sextupole &) override;
    void draw(const Beam &beam) override;

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
     * @param position Position of the object
     * @param scale Scale of the object
     * @return
     */
    QMatrix4x4 posToModel(const Vector3D &position, double scale);
    /**
     * Whether the eye is forced inside the accelerator by the ViewMode.
     */
    bool viewInsideAccelerator() { return viewMode == FIRST_PERSON || viewMode == THIRD_PERSON; }

    /**
     * Whether Elements drawn should be lit or not
     */
    bool elementsLighting() { return theme()->isElementFilled() && !viewInsideAccelerator(); }
    void sendPoint(const Vector3D &point) { prog.setAttributeValue(VertexId, point.x(), point.y(), point.z()); };
    void sendNormal(const Vector3D &normal = Vector3D(2, 2, 4)) { glNormal3f(normal.x(), normal.y(), normal.z()); }

};


#endif //PARTICLEACCELERATOR_QTSUPPORT_H
