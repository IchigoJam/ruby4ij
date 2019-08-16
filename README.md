# Ruby_for_IchigoJam

ruby4ij - Ruby language for IchigoJam

Let's make program in Ruby language on your PC!  
This tool provide to convert mruby 2.0 file to bin file for IchigoJam BASIC.  
* For IchigoJam BASIC 1.4b9 or higher for LPC1114  
https://github.com/IchigoJam/IchigoJam.github.io  

see also  
https://fukuno.jig.jp/2579  


## Example

```
cls; x=15
while true
  lc x,5; p 79 
  lc rnd(32),23; p 42; p 10
  wait 3
  k=inkey()
  x=x-(k==28?1:0)+(k==29?1:0)
  if scr(x,5)!=0
    break
  end
end
```
ruby/kawakudari.rb  

## How to use

Edit settings to fit your environment  

write Ruby VM to your IchigoJam
```
$ make write  
```

write Ruby program to your IchigoJam  
```
$ make mrbc  
```

## How to extend

edit src/main.c  
```
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
```

## License

CC BY 4.0 http://ichigojam.net/  
