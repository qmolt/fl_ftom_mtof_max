#include "fl_ftom.h"

void C74_EXPORT main() {

	t_class *c;

	c = class_new("fl_ftom",(method)fl_ftom_new, (method)NULL,sizeof(t_fl_ftom), 0, 0);
	class_addmethod(c, (method)fl_ftom_assist,"assist", A_CANT, 0);
	class_addmethod(c,(method)fl_ftom_entero, "int", A_LONG, 0);
	class_addmethod(c,(method)fl_ftom_float, "float", A_LONG, 0);
	class_addmethod(c,(method)fl_ftom_afin, "afin_a4", A_GIMME, 0);
	class_addmethod(c,(method)fl_ftom_oct, "mult_oct", A_GIMME, 0);
	class_addmethod(c,(method)fl_ftom_div, "div_oct", A_GIMME, 0);
	class_addmethod(c, (method)fl_ftom_a4, "a4", A_GIMME, 0);

	class_register(CLASS_BOX, c);
	fl_ftom_class = c; 
}

void *fl_ftom_new(t_symbol *s, short argc, t_atom *argv) 
{
	t_fl_ftom *x = (t_fl_ftom *)object_alloc(fl_ftom_class);

	x->m_outlet = floatout((t_object *)x);

	x->afin = AFIN_STDR;
	x->div = DIV_OCT_STDR;
	x->oct = MULT_OCT_STDR;
	x->afour = AFOUR_STDR;

	return x;
}

void fl_ftom_assist(t_fl_ftom *x, void *b, long msg, long arg, char *dst)
{
	if (msg == ASSIST_INLET) {										
		switch (arg) {
		case I_INPUT: 
			sprintf(dst, "nota midi"); 
			break;
		}
	}
	else if (msg == ASSIST_OUTLET) {    
		switch (arg) {
		case O_OUTPUT: 
			sprintf(dst, "frecuencia"); 
			break;
		}
	}
}

void fl_ftom_entero(t_fl_ftom *x, long n) 
{
	fl_ftom_float(x, (float)n);
}

void fl_ftom_float(t_fl_ftom *x, double f) 
{
	double m = (x->div * log(f / x->afin) / log(x->oct)) + x->afour;
	outlet_float(x->m_outlet, m);
}

void fl_ftom_afin(t_fl_ftom *x, t_symbol *s, long argc, t_atom *argv)
{
	float afin;
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }
	afin = (float)atom_getfloat(av);
//	if (afin <= 0.0) { return; }
	x->afin = afin;
}
void fl_ftom_oct(t_fl_ftom *x, t_symbol *s, long argc, t_atom *argv)
{
	float oct;
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }
	oct = (float)atom_getfloat(av);
//	if (oct <= 0.0) { return; }
	x->oct = oct;
}
void fl_ftom_div(t_fl_ftom *x, t_symbol *s, long argc, t_atom *argv)
{
	float div;
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }
	div = (float)atom_getfloat(av);
//	if (div <= 0.0) { return; }
	x->div = div;
}
void fl_ftom_a4(t_fl_ftom *x, t_symbol *s, long argc, t_atom *argv)
{
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }

	x->afour = (float)atom_getfloat(av);
}