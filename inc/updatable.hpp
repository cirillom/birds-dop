#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP

class Updatable {
public:
    virtual void update() = 0; // Pure virtual method
    virtual ~Updatable() {}    // Virtual destructor
};

#endif // UPDATABLE_HPP