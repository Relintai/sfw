// -----------------------------------------------------------------------------
// time framework utils
// - rlyeh, public domain.

API uint64_t    date();        // YYYYMMDDhhmmss
API uint64_t    date_epoch();  // linux epoch
API char*       date_string(); // "YYYY-MM-DD hh:mm:ss"
API double      time_hh();
API double      time_mm();
API double      time_ss();
API uint64_t    time_ms();
API uint64_t    time_us();
API uint64_t    time_ns();
API void        sleep_ss(double ss);
API void        sleep_ms(double ms);
API void        sleep_us(double us);
API void        sleep_ns(double us);

API unsigned    timer(unsigned ms, unsigned (*callback)(unsigned ms, void *arg), void *arg);
API void        timer_destroy(unsigned timer_handle);

