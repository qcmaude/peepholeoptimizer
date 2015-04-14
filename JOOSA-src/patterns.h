/*
 * JOOS is Copyright (C) 1997 Laurie Hendren & Michael I. Schwartzbach
 *
 * Reproduction of all or part of this software is permitted for
 * educational or research use on condition that this copyright notice is
 * included in any copy. This software comes with no warranty of any
 * kind. In no event will the authors be liable for any damages resulting from
 * use of this software.
 *
 * email: hendren@cs.mcgill.ca, mis@brics.dk
 */

/* iload x        iload x        iload x
 * ldc 0          ldc 1          ldc 2
 * imul           imul           imul
 * ------>        ------>        ------>
 * ldc 0          iload x        iload x
 *                               dup
 *                               iadd
 */

int simplify_multiplication_right(CODE **c)
{ int x,k;
  if (is_iload(*c,&x) && 
      is_ldc_int(next(*c),&k) && 
      is_imul(next(next(*c)))) {
     if (k==0) return replace(c,3,makeCODEldc_int(0,NULL));
     else if (k==1) return replace(c,3,makeCODEiload(x,NULL));
     else if (k==2) return replace(c,3,makeCODEiload(x,
                                       makeCODEdup(
                                       makeCODEiadd(NULL))));
     return 0;
  }
  return 0;
}

/* dup
 * astore x
 * pop
 * -------->
 * astore x
 */
int simplify_astore(CODE **c)
{ int x;
  if (is_dup(*c) &&
      is_astore(next(*c),&x) &&
      is_pop(next(next(*c)))) {
     return replace(c,3,makeCODEastore(x,NULL));
  }
  return 0;
}

/*
*
*/
int multiple_constant_folding(CODE **c) 
{ int x, y;
  if(is_ldc_int(*c,&x) &&
    is_ldc_int(next(*c),&y)) {

      if(is_iadd(next(next(*c)))){
        return replace(c, 2, makeCODEldc_int(x+y, NULL));    
      } else if (is_isub(next(next(*c)))) {
        return replace(c, 2, makeCODEldc_int(x-y, NULL));    
      } else if (is_imul(next(next(*c)))) {
        return replace(c, 2, makeCODEldc_int(x*y, NULL));    
      } else if (is_idiv(next(next(*c)))) {
        return replace(c, 2, makeCODEldc_int(x/y, NULL));    
      } else if (is_irem(next(next(*c)))) {
        return replace(c, 2, makeCODEldc_int(x%y, NULL));    
      }

    }
  return 0;
}

int simplify_istore(CODE **c)
{ int x;
  if (is_dup(*c) &&
      is_istore(next(*c),&x) &&
      is_pop(next(next(*c)))) {
     return replace(c,3,makeCODEistore(x,NULL));
  }
  return 0;
}

/* iload x
 * ldc k   (0<=k<=127)
 * iadd
 * istore x
 * --------->
 * iinc x k
 */ 
int positive_increment(CODE **c)
{ int x,y,k;
  if (is_iload(*c,&x) &&
      is_ldc_int(next(*c),&k) &&
      is_iadd(next(next(*c))) &&
      is_istore(next(next(next(*c))),&y) &&
      x==y && 0<=k && k<=127) {
     return replace(c,4,makeCODEiinc(x,k,NULL));
  }
  return 0;
}

/* goto L1
 * ...
 * L1:
 * goto L2
 * ...
 * L2:
 * --------->
 * goto L2
 * ...
 * L1:    (reference count reduced by 1)
 * goto L2
 * ...
 * L2:    (reference count increased by 1)  
 */
int simplify_goto_goto(CODE **c)
{ int l1,l2;
  if (is_goto(*c,&l1) && is_goto(next(destination(l1)),&l2) && l1>l2) {
     droplabel(l1);
     copylabel(l2);
     return replace(c,1,makeCODEgoto(l2, NULL));
  }
  return 0;
}

/* goto L1
 * ...
 * L1:
 * return
 * --------->
 * return
 * ...
 * L1:  (reference count reduced by 1)
 * return
 */
int simplify_label_goto(CODE **c)
{ int l1;
  if (is_goto(*c,&l1) && is_return(next(destination(l1)))) {
     droplabel(l1);
     return replace(c,1,makeCODEreturn(NULL));
  }
  return 0;
}

/* iload x
 * ldc k   (0<=k<=127)
 * isub
 * istore x
 * --------->
 * iinc x -k
 */ 
int negative_increment(CODE **c) 
{ int x,y,k;
  if (is_iload(*c,&x) &&
      is_ldc_int(next(*c),&k) &&
      is_isub(next(next(*c))) &&
      is_istore(next(next(next(*c))),&y) &&
      x==y && 0<=k && k<=127) {
     return replace(c,4,makeCODEiinc(x,-k,NULL));
  }
  return 0;
}

/* 
 * aload x 
 * pop
 * ------->
 * //Nothing...
 */
int remove_push_pop(CODE **c) 
{
  if (is_simplepush(*c) &&
      is_pop(next(*c))) {
     return replace(c, 2, NULL);
  }
  return 0;
}


/* dup
 * aload x
 * swap
 * putfield ...
 * pop
 * ------->
 * aload x
 * swap
 * putfield ...
 */
int remove_dup_aload_swap_putfield_pop(CODE **c) {
  int al;
  char* pf;
  if(is_dup(*c) &&
    is_aload(next(*c), &al) &&
    is_swap(next(next(*c))) &&
    is_putfield(next(next(next(*c))), &pf) && 
    is_pop(nextby(*c, 4))) {
    return replace(c, 5, makeCODEaload(al, makeCODEswap(makeCODEputfield(pf, NULL))));
  }
  return 0;
}

/* goto L1
 * ... (All labels in this section are dead)
 * L3:
 * -------->
 * goto L1
 * L3:
 */
int remove_block(CODE **c) {
  int l1, l2;
  if(is_goto(*c, &l1)){
    CODE *curr = next(*c);
    int i = 1;
    while (curr){
	  if (is_label(curr, &l2) && !deadlabel(l2)){
		return 0;
	  }
      curr = next(curr);
      i++;
    }
    return replace_modified(c, i, makeCODEgoto(l1, NULL));
  }
  return 0;
}

/* L1: (L1 is a dead label)
 * --------->
 * // Nothing
 */
int remove_dead_label(CODE **c) {
  int l1;
  if(is_label(*c, &l1) &&
    deadlabel(l1)) {
    return kill_line(c);
  }
  return 0;
}

/* 
 * 
 * 
 * 
 * 
 */
int simplify_ifcmp(CODE **c) {
  int k, l1;
  if(is_ldc_int(*c, &k) && k == 0) {
    if(is_if_icmpeq(next(*c), &l1)) {
      return replace(c, 2, makeCODEifeq(l1, NULL));
    } else if(is_if_icmpne(next(*c), &l1)) {
      return replace(c, 2, makeCODEifne(l1, NULL));
    }
  }
  return 0;
}

/* nop
 * ------->
 * // Nothing
 */
int remove_nop(CODE **c) {
  if(is_nop(*c)) {
    return kill_line(c);
  }
  return 0;
}

/* astore n
 * aload n
 * ... (No loads of n or branches before a store of n)
 * --------> 
 * ... (No loads of n or branches before a store of n)
 */
int remove_astore_aload(CODE **c){
  int i1, i2, l;
  if(is_astore(*c, &i1) && 
		  is_aload(next(*c), &i2) && 
		  i1 == i2){
    CODE *curr = next(next(*c));
	while (curr){
		if (is_return(curr) || 
				is_areturn(curr) || 
				is_ireturn(curr) ||
				(is_astore(curr, &i2) && i1 == i2)){
			return replace(c, 2, NULL);
		} else if (is_if(&curr, &l) || 
				(is_aload(curr, &i2) && 
				 i1 == i2)){
			return 0;
		} else if (is_goto(curr, &l)){
			curr = destination(l);
		}
		curr = next(curr);
	}
  }
  return 0;
}

int remove_dumb_aload_swap(CODE **c){
	int i1, i2;
	if (is_aload(*c, &i1) &&
			is_aload(next(*c), &i2) &&
			is_swap(next(next(*c)))){
		return replace(c, 3, makeCODEaload(i2, makeCODEaload(i1, NULL)));
	}
	return 0;
}

#define OPTS 16

OPTI optimization[OPTS] = {remove_nop,
						   simplify_astore,
                           simplify_istore,
                           simplify_multiplication_right,
                           multiple_constant_folding,
                           positive_increment,
                           negative_increment,
                           simplify_goto_goto,
                           simplify_label_goto,
                           simplify_ifcmp,
                           remove_block,
                           remove_push_pop,
                           remove_dup_aload_swap_putfield_pop,
                           remove_dead_label,
						   remove_astore_aload,
						   remove_dumb_aload_swap
                           };
