#ifndef EXITER_HPP
#define EXITER_HPP

class Exiter {
private:
    static Exiter instance;
    bool shouldClose;
    Exiter() : shouldClose{false} {};
public:
    Exiter(const Exiter&) = delete;
    static Exiter& Get() {
        return instance;
    }

    bool ShouldCloseGame() {
        return shouldClose;
    }

    void CloseGame() {
        shouldClose = true;
    }
    ~Exiter() = default;
};

Exiter Exiter::instance;


#endif