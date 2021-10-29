#include "flmtof.h"

void C74_EXPORT main() {

	t_class *c;

	c = class_new("flmtof",(method)fl_mtof_new, (method)NULL,sizeof(t_fl_mtof), 0, 0);
	class_addmethod(c, (method)fl_mtof_assist,"assist", A_CANT, 0);

	class_addmethod(c, (method)fl_mtof_entero, "int", A_LONG, 0);
	class_addmethod(c, (method)fl_mtof_float, "float", A_FLOAT, 0);
	class_addmethod(c, (method)fl_mtof_frec0, "frec0", A_GIMME, 0);
	class_addmethod(c, (method)fl_mtof_oct, "mult_oct", A_GIMME, 0);
	class_addmethod(c, (method)fl_mtof_div, "div_oct", A_GIMME, 0);
	class_addmethod(c, (method)fl_mtof_midi0, "midi0", A_GIMME, 0);

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
	
	x->frec0 = FREC0_STDR;
	x->div = DIV_OCT_STDR;
	x->oct = MULT_OCT_STDR;
	x->midi0 = MIDI0_STDR;

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

void fl_mtof_float(t_fl_mtof *x, double f)
{
	double nota = f;
	double frec = x->frec0 * (pow(x->oct, (nota - x->midi0) / x->div));
	outlet_float(x->m_outlet, frec);
}

void fl_mtof_frec0(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv)
{
	float newfrec;
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }

	newfrec = (float)atom_getfloat(av);
	if (newfrec <= 0.0) { return; }
	x->frec0 = newfrec;
}
void fl_mtof_oct(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv)
{
	float oct;
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }

	oct = (float)atom_getfloat(av);
	if (oct <= 0) { return; }
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
	if (div <= 0) { return; }

	x->div = div;
}
void fl_mtof_midi0(t_fl_mtof *x, t_symbol *s, long argc, t_atom *argv)
{
	long ac = argc;
	t_atom *av = argv;
	if (!ac) { return; }
	if (atom_gettype(av) != A_LONG && atom_gettype(av) != A_FLOAT) { return; }

	x->midi0 = (float)atom_getfloat(av);
}