.class public FlipBoardMove

.super Move

.method public <init>()V
  .limit locals 1
  .limit stack 1
  aload_0
  invokenonvirtual Move/<init>()V
  return
.end method

.method public apply(IILBoard;Ljava/lang/Character;)V
  .limit locals 11
  .limit stack 6
  aload_3
  invokevirtual Board/getWidth()I
  istore 7
  aload_3
  invokevirtual Board/getHeight()I
  istore 8
  new Board
  dup
  iload 7
  iload 8
  invokenonvirtual Board/<init>(II)V
  astore 10
  iconst_0
  istore 5
  start_0:
  iload 5
  iload 7
  if_icmplt true_2
  iconst_0
  goto stop_3
  true_2:
  iconst_1
  stop_3:
  ifeq stop_1
  iload 8
  iconst_1
  isub
  istore 6
  start_4:
  iload 6
  iconst_0
  if_icmpge true_6
  iconst_0
  goto stop_7
  true_6:
  iconst_1
  stop_7:
  ifeq stop_5
  aload_3
  iload 5
  iload 6
  invokevirtual Board/get(II)Ljava/lang/Character;
  astore 9
  aload 10
  iload 5
  aload 9
  invokevirtual Board/place(ILjava/lang/Character;)V
  iinc 6 -1
  goto start_4
  stop_5:
  iinc 5 1
  goto start_0
  stop_1:
  iconst_0
  istore 5
  start_8:
  iload 5
  iload 7
  if_icmplt true_10
  iconst_0
  goto stop_11
  true_10:
  iconst_1
  stop_11:
  ifeq stop_9
  iconst_0
  istore 6
  start_12:
  iload 6
  iload 8
  if_icmplt true_14
  iconst_0
  goto stop_15
  true_14:
  iconst_1
  stop_15:
  ifeq stop_13
  aload_3
  iload 5
  iload 6
  aload 10
  iload 5
  iload 6
  invokevirtual Board/get(II)Ljava/lang/Character;
  invokevirtual Board/set(IILjava/lang/Character;)V
  iinc 6 1
  goto start_12
  stop_13:
  iinc 5 1
  goto start_8
  stop_9:
  return
.end method

.method public toString()Ljava/lang/String;
  .limit locals 1
  .limit stack 1
  ldc "Flip Board: flips the board upside down."
  areturn
.end method

