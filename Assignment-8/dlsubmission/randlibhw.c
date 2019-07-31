#include <immintrin.h>
#include "randlib.h" 


/* Hardware implementation.  */


/* Initialize the hardware rand64 implementation.  */
__attribute__ ((__constructor__))
static void
hardware_rand64_init (void)
{
}

/* Return a random value, using hardware operations.  */
static unsigned long long
hardware_rand64 (void)
{
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}

/* Finalize the hardware rand64 implementation.  */
__attribute__ ((__destructor__))
static void
hardware_rand64_fini (void)
{
}

/* Returns the function hardware_rand64 */
extern unsigned long long rand64 (void)
{
  return hardware_rand64();
}
