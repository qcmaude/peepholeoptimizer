.class public KillRowMove

.super Move

.method public <init>()V
  .limit locals 1
  .limit stack 1
  aload_0
  invokenonvirtual Move/<init>()V
  return
.end method

.method public apply(IILBoard;Ljava/lang/Character;)V
  .limit locals 6
  .limit stack 3
  iconst_0
  istore 5
  start_0:
  iload 5
  aload_3
  invokevirtual Board/getWidth()I
  if_icmplt true_2
  iconst_0
  goto stop_3
  true_2:
  iconst_1
  stop_3:
  ifeq stop_1
  aload_3
  iload 5
  iload_2
  invokevirtual Board/clear(II)V
  iinc 5 1
  goto start_0
  stop_1:
  return
.end method

.method public toString()Ljava/lang/String;
  .limit locals 1
  .limit stack 1
  ldc "Kill Row: clears the row where the token lands."
  areturn
.end method

