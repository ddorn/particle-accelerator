/**
 * Base class for all contents
 *
 * A Content is anything that we may want to draw, render or
 * write somewhere. We are using a double dispatch mechanism
 * in order to use any support with any content. One notable
 * difference between our implementation and the provided is
 * that no content has a Support, for two reasons :
 *  - This way, we can draw contents on multiple supports at
 *      the same time (qt view and text output for instance)
 *  - We don't need to pass Supports to each constructor and
 *      then store it when it does little sense.
 *  Therefore, a Support is handed to the draw that dispatch
 *  the call to the support.
 */

#ifndef PARTICLEACCELERATOR_CONTENT_H
#define PARTICLEACCELERATOR_CONTENT_H

class Support;

class Content {
public:
    virtual ~Content() = default;
    virtual void draw(Support &support) const = 0;
};


#endif //PARTICLEACCELERATOR_CONTENT_H
