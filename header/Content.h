/**
 *
 * \authors D.Dorn G.Kolly
 */
#ifndef PARTICLEACCELERATOR_CONTENT_H
#define PARTICLEACCELERATOR_CONTENT_H

class Support;


class Content {
protected:
    Support* support_;

public:
    explicit Content(Support* support) : support_(support) {}
    virtual ~Content() = default;
    virtual void draw() = 0;
};


#endif //PARTICLEACCELERATOR_CONTENT_H
