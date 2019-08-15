#include <std15.h>

#define x_printf
#include <mruby_l1vm.h>

void emb_method(struct mrb_vm* vm, const char* func, intptr_t* reg, int a, int paramlen) {
	if (mrb_strcmp(func, "cls") == 0) {
		cls();
	} else if (mrb_strcmp(func, "lc") == 0) {
		locate(reg[a + 1], reg[a + 2]);
	} else if (mrb_strcmp(func, "scr") == 0) {
		reg[a] = scr(reg[a + 1], reg[a + 2]);
	} else if (mrb_strcmp(func, "inkey") == 0) {
		reg[a] = inkey();
	} else if (mrb_strcmp(func, "rnd") == 0) {
		reg[a] = rnd(reg[a + 1]);
	} else if (mrb_strcmp(func, "wait") == 0) {
		wait(reg[a + 1]);
	} else if (mrb_strcmp(func, "!=") == 0) {
		intptr_t ret = reg[a] != reg[a + 1] ? MRB_TRUE : MRB_FALSE;
		reg[a] = ret;
	} else if (mrb_strcmp(func, "p") == 0) {
		putc(reg[a + 1]);
	} else if (mrb_strcmp(func, "print") == 0) {
		putstr((const char*)reg[a + 1]);
	} else {
		x_printf("no methods err!!\n");
		vm->err = MRB_ERR_NO_METHOD;
	}
}

__attribute__ ((section(".main")))
int main(int param, int ram, int rom, uint64_t (*divfunc)()) {
	//uint8_t* mrbfile = (uint8_t*)ram + 0x700; // under 256byte
	uint8_t* mrbfile = (uint8_t*)0x6400; // sector6-1, limit 3kb
	struct mrb_vm vm;
	mrb_vm_init(&vm);
	return mrb_run(&vm, mrbfile);
}
