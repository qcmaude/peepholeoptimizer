.class public DiagBombMove

.super Move

.method public <init>()V
  .limit locals 1
  .limit stack 1
  aload_0
  invokenonvirtual Move/<init>()V
  return
.end method

.method public apply(IILBoard;Ljava/lang/Character;)V
  .limit locals 9
  .limit stack 3
  aload_3
  invokevirtual Board/getWidth()I
  istore 7
  aload_3
  invokevirtual Board/getHeight()I
  istore 8
  iload_2
  iconst_1
  isub
  istore 6
  iload_1
  iconst_1
  isub
  istore 5
  start_0:
  iload 5
  iconst_0
  if_icmpge true_2
  iconst_0
  goto stop_3
  true_2:
  iconst_1
  stop_3:
  ifeq stop_1
  aload_3
  iload 5
  iload 6
  invokevirtual Board/inRange(II)Z
  ifeq stop_4
  aload_3
  iload 5
  iload 6
  invokevirtual Board/clear(II)V
  stop_4:
  iinc 6 -1
  iinc 5 -1
  goto start_0
  stop_1:
  iload_2
  iconst_1
  isub
  istore 6
  iload_1
  iconst_1
  iadd
  istore 5
  start_5:
  iload 5
  iload 7
  if_icmplt true_7
  iconst_0
  goto stop_8
  true_7:
  iconst_1
  stop_8:
  ifeq stop_6
  aload_3
  iload 5
  iload 6
  invokevirtual Board/inRange(II)Z
  ifeq stop_9
  aload_3
  iload 5
  iload 6
  invokevirtual Board/clear(II)V
  stop_9:
  iinc 6 -1
  iinc 5 1
  goto start_5
  stop_6:
  iload_2
  iconst_1
  iadd
  istore 6
  iload_1
  iconst_1
  isub
  istore 5
  start_10:
  iload 5
  iconst_0
  if_icmpge true_12
  iconst_0
  goto stop_13
  true_12:
  iconst_1
  stop_13:
  ifeq stop_11
  aload_3
  iload 5
  iload 6
  invokevirtual Board/inRange(II)Z
  ifeq stop_14
  aload_3
  iload 5
  iload 6
  invokevirtual Board/clear(II)V
  stop_14:
  iinc 6 1
  iinc 5 -1
  goto start_10
  stop_11:
  iload_2
  iconst_1
  iadd
  istore 6
  iload_1
  iconst_1
  iadd
  istore 5
  start_15:
  iload 5
  iload 7
  if_icmplt true_17
  iconst_0
  goto stop_18
  true_17:
  iconst_1
  stop_18:
  ifeq stop_16
  aload_3
  iload 5
  iload 6
  invokevirtual Board/inRange(II)Z
  ifeq stop_19
  aload_3
  iload 5
  iload 6
  invokevirtual Board/clear(II)V
  stop_19:
  iinc 6 1
  iinc 5 1
  goto start_15
  stop_16:
  return
.end method

.method public toString()Ljava/lang/String;
  .limit locals 1
  .limit stack 1
  ldc "Diagonal Bomb: clears the contents of diagonal cells."
  areturn
.end method

