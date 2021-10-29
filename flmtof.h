#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"  

#define FREC0_STDR 440.0
#define DIV_OCT_STDR 12.0
#define MULT_OCT_STDR 2.0
#define MIDI0_STDR 69

enum INLETS { I_INPUT, NUM_INLETS };
enum OUTLETS { O_OUTPUT, NUM_OUTLETS };

typedef struct {

	t_object obj;
	float frec0;
	float oct;
	float div;
	float midi0;
	void *m_outlet;

} t_fl_mtof;

void *fl_mtof_new(t_symbol *s, short argc, t_atom *argv);
void *fl_mtof_common_new(t_fl_mtof *x, short argc, t_atom *argv);
void fl_mtof_assist(t_fl_mtof *x, void *b, long msg, long arg, char *dst);

void fl_mtof_entero(t_fl_mtof *x, long n);
void fl_mtof_float(t_fl_mtof *x, double f);
void fl_mtof_frec0(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv);
void fl_mtof_oct(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv);
void fl_mtof_div(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv);
void fl_mtof_midi0(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv);

static t_class *fl_mtof_class;