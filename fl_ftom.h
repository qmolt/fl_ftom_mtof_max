#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"  
#include <math.h>

#define AFIN_STDR 440.0
#define DIV_OCT_STDR 12.0
#define MULT_OCT_STDR 2.0
#define AFOUR_STDR 69.0

enum INLETS { I_INPUT, NUM_INLETS };
enum OUTLETS { O_OUTPUT, NUM_OUTLETS };

typedef struct {

	t_object obj;
	float afin;
	float oct;
	float div;
	float afour;
	void *m_outlet;

} t_fl_ftom;

void *fl_ftom_new(t_symbol *s, short argc, t_atom *argv);
void fl_ftom_assist(t_fl_ftom *x, void *b, long msg, long arg, char *dst);

void fl_ftom_entero(t_fl_ftom *x, long n);	//send to float
void fl_ftom_float(t_fl_ftom *x, double f); //makes the calculation
void fl_ftom_afin(t_fl_ftom *x, t_symbol *s, long argc, t_atom *argv); //central A4 frequency. 440Hz by default
void fl_ftom_oct(t_fl_ftom *x, t_symbol *s, long argc, t_atom *argv); //the ratio between fundamentals that makes an 'octave', by deafult 2
void fl_ftom_div(t_fl_ftom *x, t_symbol *s, long argc, t_atom *argv); //number of division of an 'octave', 12 by default
void fl_ftom_a4(t_fl_ftom *x, t_symbol *s, long argc, t_atom *argv); //a4: central 'A4' midi note, 69 by deafult

static t_class *fl_ftom_class;