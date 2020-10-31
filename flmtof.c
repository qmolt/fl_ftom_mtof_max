#include "flmtof.h"

void C74_EXPORT main() {

	t_class *c;

	c = class_new("flmtof",(method)fl_mtof_new, (method)NULL,sizeof(t_fl_mtof), 0, 0);
	class_addmethod(c, (method)fl_mtof_assist,"assist", A_CANT, 0);

	class_addmethod(c, (method)fl_mtof_entero, "int", A_LONG, 0);
	class_addmethod(c, (method)fl_mtof_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)fl_mtof_afin, "afin_a4", A_GIMME, 0);
	class_addmethod(c, (method)fl_mtof_oct, "mult_oct", A_GIMME, 0);
	class_addmethod(c, (method)fl_mtof_div, "div_oct", A_GIMME, 0);
	class_addmethod(c, (method)fl_mtof_a4, "a4", A_GIMME, 0);

	class_register(CLASS_BOX, c);
	fl_mtof_class = c; 	
}

void *fl_mtof_new(t_symbol *s, short argc, t_atom *argv) 				
{
	t_fl_mtof *x = (t_fl_mtof *)object_alloc(fl_mtof_class);			
	return fl_mtof_common_new(x, argc, argv);						
}

void *fl_mtof_common_new(t_fl_mtof *x, short argc, t_atom *argv)
{
	x->m_outlet = floatout((t_object *)x);				
	
	x->afin = AFIN_STDR;
	x->div = DIV_OCT_STDR;
	x->oct = MULT_OCT_STDR;
	x->afour = AFOUR_STDR;

	return x;
}

void fl_mtof_assist(t_fl_mtof *x, void *b, long msg, long arg, char *dst)
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

void fl_mtof_entero(t_fl_mtof *x, long n)
{
	float f = (float)n;
	fl_mtof_float(x, f);
}

void fl_mtof_float(t_fl_mtof *x, float f)
{
	float nota = f;
	float frec = (float)(x->afin * (pow(x->oct, (nota - x->afour) / x->div)));
	outlet_float(x->m_outlet, frec);
}

void fl_mtof_afin(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv)
{
	float afin;
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }

	afin = (float)atom_getfloat(av);
//	if (afin <= 0) { return; }
	x->afin = afin;
}
void fl_mtof_oct(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv)
{
	float oct;
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }

	oct = (float)atom_getfloat(av);
//	if (oct <= 0) { return; }
	x->oct = oct;
}
void fl_mtof_div(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv)
{
	float div;
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }

	div = (float)atom_getfloat(av);
//	if (div <= 0) { return; }

	x->div = div;
}
void fl_mtof_a4(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv)
{
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }

	x->afour = (float)atom_getfloat(av);
}