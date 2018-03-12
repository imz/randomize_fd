* Test the socket() wrapper.
* `dlsym (RTLD_NEXT, "open")` doesn't get exactly the same version as
  would be used without our intervention. (Reported by ldv.)
