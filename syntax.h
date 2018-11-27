/*
syntax.h
*/
#ifndef __SYNTAX_H__
#define __SYNTAX_H__ 1
#ifdef  __cplusplus
extern "C" {
#endif
#define MAX_BINARY_OPERATOR_PRECEDENCE 10
#define START_CMD 351
#define END_CMD 885
#define NUM_CMD 535

#include "memory.h"
#include "builder.h"
#include "execute.h"

#define CMD_RTRIM 351
void COMMAND_RTRIM(pExecuteObject);
#define CMD_EXTOPHD 352
void COMMAND_EXTOPHD(pExecuteObject);
#define CMD_IMIN 353
void COMMAND_IMIN(pExecuteObject);
#define CMD_EXTOPFH 354
void COMMAND_EXTOPFH(pExecuteObject);
#define CMD_EXTOPPL 355
void COMMAND_EXTOPPL(pExecuteObject);
#define CMD_FREEFILE 356
void COMMAND_FREEFILE(pExecuteObject);
#define CMD_EXTOPFJ 357
void COMMAND_EXTOPFJ(pExecuteObject);
#define CMD_EXTOPBD 358
void COMMAND_EXTOPBD(pExecuteObject);
#define CMD_EXTOPCH 359
void COMMAND_EXTOPCH(pExecuteObject);
#define CMD_EXTOPKE 360
void COMMAND_EXTOPKE(pExecuteObject);
#define CMD_ASIN 361
void COMMAND_ASIN(pExecuteObject);
#define CMD_ERRORDOLLAR 362
void COMMAND_ERRORDOLLAR(pExecuteObject);
#define CMD_LETC 363
void COMMAND_LETC(pExecuteObject);
#define CMD_EXTOPDP 364
void COMMAND_EXTOPDP(pExecuteObject);
#define CMD_LABEL 875
#define CMD_UNPACK 365
void COMMAND_UNPACK(pExecuteObject);
#define CMD_EXTOPQL 366
void COMMAND_EXTOPQL(pExecuteObject);
#define CMD_EQ 367
void COMMAND_EQ(pExecuteObject);
#define CMD_EXTOPEO 368
void COMMAND_EXTOPEO(pExecuteObject);
#define CMD_EXTOPGC 369
void COMMAND_EXTOPGC(pExecuteObject);
#define CMD_EXTOPF 370
void COMMAND_EXTOPF(pExecuteObject);
#define CMD_NOW 371
void COMMAND_NOW(pExecuteObject);
#define CMD_IMAX 372
void COMMAND_IMAX(pExecuteObject);
#define CMD_ISARRAY 373
void COMMAND_ISARRAY(pExecuteObject);
#define CMD_ONERRORRESUMENEXT 374
void COMMAND_ONERRORRESUMENEXT(pExecuteObject);
#define CMD_UBOUND 375
void COMMAND_UBOUND(pExecuteObject);
#define CMD_RND 376
void COMMAND_RND(pExecuteObject);
#define CMD_UNDEF 377
void COMMAND_UNDEF(pExecuteObject);
#define CMD_EXTOPIM 378
void COMMAND_EXTOPIM(pExecuteObject);
#define CMD_EXTOPKC 379
void COMMAND_EXTOPKC(pExecuteObject);
#define CMD_GCONST 876
#define CMD_ASECANT 380
void COMMAND_ASECANT(pExecuteObject);
#define CMD_RESUMENEXT 381
void COMMAND_RESUMENEXT(pExecuteObject);
#define CMD_VAL 382
void COMMAND_VAL(pExecuteObject);
#define CMD_EXTOPGK 383
void COMMAND_EXTOPGK(pExecuteObject);
#define CMD_ABS 384
void COMMAND_ABS(pExecuteObject);
#define CMD_EXTOPME 385
void COMMAND_EXTOPME(pExecuteObject);
#define CMD_CVL 386
void COMMAND_CVL(pExecuteObject);
#define CMD_EXTOPQF 387
void COMMAND_EXTOPQF(pExecuteObject);
#define CMD_EXTOPNP 388
void COMMAND_EXTOPNP(pExecuteObject);
#define CMD_SLIF 389
void COMMAND_SLIF(pExecuteObject);
#define CMD_GCD 390
void COMMAND_GCD(pExecuteObject);
#define CMD_EXTOPGQ 391
void COMMAND_EXTOPGQ(pExecuteObject);
#define CMD_WDAY 392
void COMMAND_WDAY(pExecuteObject);
#define CMD_LETM 393
void COMMAND_LETM(pExecuteObject);
#define CMD_EXTOPAG 394
void COMMAND_EXTOPAG(pExecuteObject);
#define CMD_EXTOPL 395
void COMMAND_EXTOPL(pExecuteObject);
#define CMD_RETURNC 396
void COMMAND_RETURNC(pExecuteObject);
#define CMD_EXTOPHO 397
void COMMAND_EXTOPHO(pExecuteObject);
#define CMD_CREATEPROCESSEX 398
void COMMAND_CREATEPROCESSEX(pExecuteObject);
#define CMD_GOTO 399
void COMMAND_GOTO(pExecuteObject);
#define CMD_YDAY 400
void COMMAND_YDAY(pExecuteObject);
#define CMD_ENDMODULE 877
#define CMD_EXTOPOH 401
void COMMAND_EXTOPOH(pExecuteObject);
#define CMD_XOR 402
void COMMAND_XOR(pExecuteObject);
#define CMD_EXTOPQC 403
void COMMAND_EXTOPQC(pExecuteObject);
#define CMD_ELSIF 404
void COMMAND_ELSIF(pExecuteObject);
#define CMD_SEC 405
void COMMAND_SEC(pExecuteObject);
#define CMD_EXTOPAD 406
void COMMAND_EXTOPAD(pExecuteObject);
#define CMD_EXTOPQJ 407
void COMMAND_EXTOPQJ(pExecuteObject);
#define CMD_EXTOPMO 408
void COMMAND_EXTOPMO(pExecuteObject);
#define CMD_EXTOPOO 409
void COMMAND_EXTOPOO(pExecuteObject);
#define CMD_ISDEF 410
void COMMAND_ISDEF(pExecuteObject);
#define CMD_EXTOPFF 411
void COMMAND_EXTOPFF(pExecuteObject);
#define CMD_EXTOPOQ 412
void COMMAND_EXTOPOQ(pExecuteObject);
#define CMD_SETFILE 413
void COMMAND_SETFILE(pExecuteObject);
#define CMD_EXTOPNI 414
void COMMAND_EXTOPNI(pExecuteObject);
#define CMD_ICALLFUN 415
void COMMAND_ICALLFUN(pExecuteObject);
#define CMD_EXTOPBQ 416
void COMMAND_EXTOPBQ(pExecuteObject);
#define CMD_EXTOPBH 417
void COMMAND_EXTOPBH(pExecuteObject);
#define CMD_ISDOUBLE 418
void COMMAND_ISDOUBLE(pExecuteObject);
#define CMD_IDIV 419
void COMMAND_IDIV(pExecuteObject);
#define CMD_EXTOPPF 420
void COMMAND_EXTOPPF(pExecuteObject);
#define CMD_EXTOPBN 421
void COMMAND_EXTOPBN(pExecuteObject);
#define CMD_DOUNTIL 422
void COMMAND_DOUNTIL(pExecuteObject);
#define CMD_LLET 423
void COMMAND_LLET(pExecuteObject);
#define CMD_ADDYEAR 424
void COMMAND_ADDYEAR(pExecuteObject);
#define CMD_LOG10 425
void COMMAND_LOG10(pExecuteObject);
#define CMD_EXTOPOL 426
void COMMAND_EXTOPOL(pExecuteObject);
#define CMD_COSECANT 427
void COMMAND_COSECANT(pExecuteObject);
#define CMD_LET 428
void COMMAND_LET(pExecuteObject);
#define CMD_BYVAL 429
void COMMAND_BYVAL(pExecuteObject);
#define CMD_FRAC 430
void COMMAND_FRAC(pExecuteObject);
#define CMD_EXTOPID 431
void COMMAND_EXTOPID(pExecuteObject);
#define CMD_EXTOPDL 432
void COMMAND_EXTOPDL(pExecuteObject);
#define CMD_FCOPY 433
void COMMAND_FCOPY(pExecuteObject);
#define CMD_EXTOPJL 434
void COMMAND_EXTOPJL(pExecuteObject);
#define CMD_EXTOPBF 435
void COMMAND_EXTOPBF(pExecuteObject);
#define CMD_ISNUMERIC 436
void COMMAND_ISNUMERIC(pExecuteObject);
#define CMD_EXTOPMQ 437
void COMMAND_EXTOPMQ(pExecuteObject);
#define CMD_DOWHILE 438
void COMMAND_DOWHILE(pExecuteObject);
#define CMD_FTMODIFY 439
void COMMAND_FTMODIFY(pExecuteObject);
#define CMD_EXTOPLN 440
void COMMAND_EXTOPLN(pExecuteObject);
#define CMD_ISEMPTY 441
void COMMAND_ISEMPTY(pExecuteObject);
#define CMD_EXTOPNM 442
void COMMAND_EXTOPNM(pExecuteObject);
#define CMD_EXTOPLJ 443
void COMMAND_EXTOPLJ(pExecuteObject);
#define CMD_ONERRORGOTO 444
void COMMAND_ONERRORGOTO(pExecuteObject);
#define CMD_GE 445
void COMMAND_GE(pExecuteObject);
#define CMD_FORTO 446
void COMMAND_FORTO(pExecuteObject);
#define CMD_CONCATENATE 447
void COMMAND_CONCATENATE(pExecuteObject);
#define CMD_EXTOPJN 448
void COMMAND_EXTOPJN(pExecuteObject);
#define CMD_EXTOPHP 449
void COMMAND_EXTOPHP(pExecuteObject);
#define CMD_FLOCK 450
void COMMAND_FLOCK(pExecuteObject);
#define CMD_SGN 451
void COMMAND_SGN(pExecuteObject);
#define CMD_EXTOPEM 452
void COMMAND_EXTOPEM(pExecuteObject);
#define CMD_LETP 453
void COMMAND_LETP(pExecuteObject);
#define CMD_EXTOPKG 454
void COMMAND_EXTOPKG(pExecuteObject);
#define CMD_ODD 455
void COMMAND_ODD(pExecuteObject);
#define CMD_EXTOPIP 456
void COMMAND_EXTOPIP(pExecuteObject);
#define CMD_SEEK 457
void COMMAND_SEEK(pExecuteObject);
#define CMD_EXTOPCI 458
void COMMAND_EXTOPCI(pExecuteObject);
#define CMD_EXTOPLD 459
void COMMAND_EXTOPLD(pExecuteObject);
#define CMD_EXTOPMI 460
void COMMAND_EXTOPMI(pExecuteObject);
#define CMD_COS 461
void COMMAND_COS(pExecuteObject);
#define CMD_EXTOPMC 462
void COMMAND_EXTOPMC(pExecuteObject);
#define CMD_EXTOPFM 463
void COMMAND_EXTOPFM(pExecuteObject);
#define CMD_EXTOPPG 464
void COMMAND_EXTOPPG(pExecuteObject);
#define CMD_FUNCTIONARG 465
void COMMAND_FUNCTIONARG(pExecuteObject);
#define CMD_EXTOPCL 466
void COMMAND_EXTOPCL(pExecuteObject);
#define CMD_NEXTI 467
void COMMAND_NEXTI(pExecuteObject);
#define CMD_SQR 468
void COMMAND_SQR(pExecuteObject);
#define CMD_JOKER 469
void COMMAND_JOKER(pExecuteObject);
#define CMD_EXTOPPD 470
void COMMAND_EXTOPPD(pExecuteObject);
#define CMD_EXTOPIE 471
void COMMAND_EXTOPIE(pExecuteObject);
#define CMD_DO 472
void COMMAND_DO(pExecuteObject);
#define CMD_ROUND 473
void COMMAND_ROUND(pExecuteObject);
#define CMD_EXTOPFC 474
void COMMAND_EXTOPFC(pExecuteObject);
#define CMD_EXTOPJI 475
void COMMAND_EXTOPJI(pExecuteObject);
#define CMD_EXTOPCD 476
void COMMAND_EXTOPCD(pExecuteObject);
#define CMD_EXTOPIH 477
void COMMAND_EXTOPIH(pExecuteObject);
#define CMD_EXTOPEC 478
void COMMAND_EXTOPEC(pExecuteObject);
#define CMD_EXTOPMN 479
void COMMAND_EXTOPMN(pExecuteObject);
#define CMD_CALL 480
void COMMAND_CALL(pExecuteObject);
#define CMD_EXTOPCC 481
void COMMAND_EXTOPCC(pExecuteObject);
#define CMD_FUNCTION 482
void COMMAND_FUNCTION(pExecuteObject);
#define CMD_EXTOPKK 483
void COMMAND_EXTOPKK(pExecuteObject);
#define CMD_NOT 484
void COMMAND_NOT(pExecuteObject);
#define CMD_EXTOPKP 485
void COMMAND_EXTOPKP(pExecuteObject);
#define CMD_EXTOPNH 486
void COMMAND_EXTOPNH(pExecuteObject);
#define CMD_GOSUB 487
void COMMAND_GOSUB(pExecuteObject);
#define CMD_EXTOPJF 488
void COMMAND_EXTOPJF(pExecuteObject);
#define CMD_ADDMONTH 489
void COMMAND_ADDMONTH(pExecuteObject);
#define CMD_ISDIR 490
void COMMAND_ISDIR(pExecuteObject);
#define CMD_EXTOPEQ 491
void COMMAND_EXTOPEQ(pExecuteObject);
#define CMD_EXTOPEI 492
void COMMAND_EXTOPEI(pExecuteObject);
#define CMD_LINPUT 493
void COMMAND_LINPUT(pExecuteObject);
#define CMD_PRINT 494
void COMMAND_PRINT(pExecuteObject);
#define CMD_VAR 878
#define CMD_LOOPWHILE 495
void COMMAND_LOOPWHILE(pExecuteObject);
#define CMD_MONTH 496
void COMMAND_MONTH(pExecuteObject);
#define CMD_EXTOPNJ 497
void COMMAND_EXTOPNJ(pExecuteObject);
#define CMD_SECANT 498
void COMMAND_SECANT(pExecuteObject);
#define CMD_LOG 499
void COMMAND_LOG(pExecuteObject);
#define CMD_CLOSEALL 500
void COMMAND_CLOSEALL(pExecuteObject);
#define CMD_EXTOPII 501
void COMMAND_EXTOPII(pExecuteObject);
#define CMD_EXTOPQG 502
void COMMAND_EXTOPQG(pExecuteObject);
#define CMD_ASC 503
void COMMAND_ASC(pExecuteObject);
#define CMD_EXTOPJC 504
void COMMAND_EXTOPJC(pExecuteObject);
#define CMD_CURDIR 505
void COMMAND_CURDIR(pExecuteObject);
#define CMD_MOD 506
void COMMAND_MOD(pExecuteObject);
#define CMD_HTAN 507
void COMMAND_HTAN(pExecuteObject);
#define CMD_EXTOPHM 508
void COMMAND_EXTOPHM(pExecuteObject);
#define CMD_LOF 509
void COMMAND_LOF(pExecuteObject);
#define CMD_COTAN2 510
void COMMAND_COTAN2(pExecuteObject);
#define CMD_EXTOPMM 511
void COMMAND_EXTOPMM(pExecuteObject);
#define CMD_EXP 512
void COMMAND_EXP(pExecuteObject);
#define CMD_ADDHOUR 513
void COMMAND_ADDHOUR(pExecuteObject);
#define CMD_ADDWEEK 514
void COMMAND_ADDWEEK(pExecuteObject);
#define CMD_FIX 515
void COMMAND_FIX(pExecuteObject);
#define CMD_REWIND 516
void COMMAND_REWIND(pExecuteObject);
#define CMD_EXTOPQ 517
void COMMAND_EXTOPQ(pExecuteObject);
#define CMD_RANDOMIZA 518
void COMMAND_RANDOMIZA(pExecuteObject);
#define CMD_EXTOPJK 519
void COMMAND_EXTOPJK(pExecuteObject);
#define CMD_EXTOPO 520
void COMMAND_EXTOPO(pExecuteObject);
#define CMD_FOWNER 521
void COMMAND_FOWNER(pExecuteObject);
#define CMD_LEN 522
void COMMAND_LEN(pExecuteObject);
#define CMD_EXTOPPO 523
void COMMAND_EXTOPPO(pExecuteObject);
#define CMD_FPRINT 524
void COMMAND_FPRINT(pExecuteObject);
#define CMD_CHDIR 525
void COMMAND_CHDIR(pExecuteObject);
#define CMD_FCRYPT 526
void COMMAND_FCRYPT(pExecuteObject);
#define CMD_EXTOPDF 527
void COMMAND_EXTOPDF(pExecuteObject);
#define CMD_EXTOPKQ 528
void COMMAND_EXTOPKQ(pExecuteObject);
#define CMD_EXTOPAN 529
void COMMAND_EXTOPAN(pExecuteObject);
#define CMD_EXTOPJP 530
void COMMAND_EXTOPJP(pExecuteObject);
#define CMD_EXTOPLP 531
void COMMAND_EXTOPLP(pExecuteObject);
#define CMD_ISUNDEF 532
void COMMAND_ISUNDEF(pExecuteObject);
#define CMD_EXTOPMG 533
void COMMAND_EXTOPMG(pExecuteObject);
#define CMD_PI 534
void COMMAND_PI(pExecuteObject);
#define CMD_EXTERNAL 535
void COMMAND_EXTERNAL(pExecuteObject);
#define CMD_EXTOPGG 536
void COMMAND_EXTOPGG(pExecuteObject);
#define CMD_EXTOPBG 537
void COMMAND_EXTOPBG(pExecuteObject);
#define CMD_EXTOPFO 538
void COMMAND_EXTOPFO(pExecuteObject);
#define CMD_EXTOPHI 539
void COMMAND_EXTOPHI(pExecuteObject);
#define CMD_EXTOPPI 540
void COMMAND_EXTOPPI(pExecuteObject);
#define CMD_EXTOPJO 541
void COMMAND_EXTOPJO(pExecuteObject);
#define CMD_FILEXISTS 542
void COMMAND_FILEXISTS(pExecuteObject);
#define CMD_TRIM 543
void COMMAND_TRIM(pExecuteObject);
#define CMD_EXTOPNN 544
void COMMAND_EXTOPNN(pExecuteObject);
#define CMD_OPTION 545
void COMMAND_OPTION(pExecuteObject);
#define CMD_EXTOPJJ 546
void COMMAND_EXTOPJJ(pExecuteObject);
#define CMD_EXITSUB 547
void COMMAND_EXITSUB(pExecuteObject);
#define CMD_EXTOPHN 548
void COMMAND_EXTOPHN(pExecuteObject);
#define CMD_EXTOPIC 549
void COMMAND_EXTOPIC(pExecuteObject);
#define CMD_EXTOPDO 550
void COMMAND_EXTOPDO(pExecuteObject);
#define CMD_SWAP 551
void COMMAND_SWAP(pExecuteObject);
#define CMD_TAN2 552
void COMMAND_TAN2(pExecuteObject);
#define CMD_GT 553
void COMMAND_GT(pExecuteObject);
#define CMD_MULT 554
void COMMAND_MULT(pExecuteObject);
#define CMD_EXTOPIQ 555
void COMMAND_EXTOPIQ(pExecuteObject);
#define CMD_ONERRORGOTONULL 556
void COMMAND_ONERRORGOTONULL(pExecuteObject);
#define CMD_HEX 557
void COMMAND_HEX(pExecuteObject);
#define CMD_EXTOPHC 558
void COMMAND_EXTOPHC(pExecuteObject);
#define CMD_TRUNCATEF 559
void COMMAND_TRUNCATEF(pExecuteObject);
#define CMD_EXTOPIN 560
void COMMAND_EXTOPIN(pExecuteObject);
#define CMD_EXTOPHG 561
void COMMAND_EXTOPHG(pExecuteObject);
#define CMD_MINUTE 562
void COMMAND_MINUTE(pExecuteObject);
#define CMD_EXTOPJM 563
void COMMAND_EXTOPJM(pExecuteObject);
#define CMD_EXTOPHJ 564
void COMMAND_EXTOPHJ(pExecuteObject);
#define CMD_EXTOPFE 565
void COMMAND_EXTOPFE(pExecuteObject);
#define CMD_MKS 566
void COMMAND_MKS(pExecuteObject);
#define CMD_LIKEOP 567
void COMMAND_LIKEOP(pExecuteObject);
#define CMD_SETWILD 568
void COMMAND_SETWILD(pExecuteObject);
#define CMD_EXTOPAF 569
void COMMAND_EXTOPAF(pExecuteObject);
#define CMD_LCASE 570
void COMMAND_LCASE(pExecuteObject);
#define CMD_SETJOKER 571
void COMMAND_SETJOKER(pExecuteObject);
#define CMD_BINMI 572
void COMMAND_BINMI(pExecuteObject);
#define CMD_EXTOPAL 573
void COMMAND_EXTOPAL(pExecuteObject);
#define CMD_EXTOPLK 574
void COMMAND_EXTOPLK(pExecuteObject);
#define CMD_MKI 575
void COMMAND_MKI(pExecuteObject);
#define CMD_STR 576
void COMMAND_STR(pExecuteObject);
#define CMD_TAN 577
void COMMAND_TAN(pExecuteObject);
#define CMD_CONF 578
void COMMAND_CONF(pExecuteObject);
#define CMD_OPEN 579
void COMMAND_OPEN(pExecuteObject);
#define CMD_ICALL 580
void COMMAND_ICALL(pExecuteObject);
#define CMD_EXTOPAI 581
void COMMAND_EXTOPAI(pExecuteObject);
#define CMD_UNTIL 582
void COMMAND_UNTIL(pExecuteObject);
#define CMD_EXTOPCJ 583
void COMMAND_EXTOPCJ(pExecuteObject);
#define CMD_RANDOMIZE 584
void COMMAND_RANDOMIZE(pExecuteObject);
#define CMD_FALSE 585
void COMMAND_FALSE(pExecuteObject);
#define CMD_JOIN 586
void COMMAND_JOIN(pExecuteObject);
#define CMD_EXTOPGF 587
void COMMAND_EXTOPGF(pExecuteObject);
#define CMD_EXTOPEN 588
void COMMAND_EXTOPEN(pExecuteObject);
#define CMD_EXTOPCG 589
void COMMAND_EXTOPCG(pExecuteObject);
#define CMD_DELETEF 590
void COMMAND_DELETEF(pExecuteObject);
#define CMD_EXTOPLE 591
void COMMAND_EXTOPLE(pExecuteObject);
#define CMD_KILL 592
void COMMAND_KILL(pExecuteObject);
#define CMD_EXITFUNC 593
void COMMAND_EXITFUNC(pExecuteObject);
#define CMD_CUNDEF 594
void COMMAND_CUNDEF(pExecuteObject);
#define CMD_RESUME 595
void COMMAND_RESUME(pExecuteObject);
#define CMD_EXTOPLC 596
void COMMAND_EXTOPLC(pExecuteObject);
#define CMD_EXTOPOI 597
void COMMAND_EXTOPOI(pExecuteObject);
#define CMD_STRREVERSE 598
void COMMAND_STRREVERSE(pExecuteObject);
#define CMD_DIV 599
void COMMAND_DIV(pExecuteObject);
#define CMD_EXTOPHQ 600
void COMMAND_EXTOPHQ(pExecuteObject);
#define CMD_EXTOPBI 601
void COMMAND_EXTOPBI(pExecuteObject);
#define CMD_ADDMINUTE 602
void COMMAND_ADDMINUTE(pExecuteObject);
#define CMD_EXTOPEK 603
void COMMAND_EXTOPEK(pExecuteObject);
#define CMD_EXTOPGN 604
void COMMAND_EXTOPGN(pExecuteObject);
#define CMD_EXTOPHL 605
void COMMAND_EXTOPHL(pExecuteObject);
#define CMD_SLEEP 606
void COMMAND_SLEEP(pExecuteObject);
#define CMD_EXTOPCO 607
void COMMAND_EXTOPCO(pExecuteObject);
#define CMD_EXTOPGJ 608
void COMMAND_EXTOPGJ(pExecuteObject);
#define CMD_EXTOPQQ 609
void COMMAND_EXTOPQQ(pExecuteObject);
#define CMD_POWER 610
void COMMAND_POWER(pExecuteObject);
#define CMD_MAX 611
void COMMAND_MAX(pExecuteObject);
#define CMD_EXTOPKI 612
void COMMAND_EXTOPKI(pExecuteObject);
#define CMD_EXTOPCE 613
void COMMAND_EXTOPCE(pExecuteObject);
#define CMD_LT 614
void COMMAND_LT(pExecuteObject);
#define CMD_HSECANT 615
void COMMAND_HSECANT(pExecuteObject);
#define CMD_EXTOPBC 616
void COMMAND_EXTOPBC(pExecuteObject);
#define CMD_EXTOPNC 617
void COMMAND_EXTOPNC(pExecuteObject);
#define CMD_ENDFUNC 618
void COMMAND_ENDFUNC(pExecuteObject);
#define CMD_COMMANDF 619
void COMMAND_COMMANDF(pExecuteObject);
#define CMD_ISLONG 620
void COMMAND_ISLONG(pExecuteObject);
#define CMD_EXTOPNQ 621
void COMMAND_EXTOPNQ(pExecuteObject);
#define CMD_EXTOPBK 622
void COMMAND_EXTOPBK(pExecuteObject);
#define CMD_SETNOJO 623
void COMMAND_SETNOJO(pExecuteObject);
#define CMD_LCM 624
void COMMAND_LCM(pExecuteObject);
#define CMD_EXTOPMK 625
void COMMAND_EXTOPMK(pExecuteObject);
#define CMD_PLUS 626
void COMMAND_PLUS(pExecuteObject);
#define CMD_EXTOPIG 627
void COMMAND_EXTOPIG(pExecuteObject);
#define CMD_EVEN 628
void COMMAND_EVEN(pExecuteObject);
#define CMD_EXTOPOM 629
void COMMAND_EXTOPOM(pExecuteObject);
#define CMD_HCTAN 630
void COMMAND_HCTAN(pExecuteObject);
#define CMD_EXTOPBL 631
void COMMAND_EXTOPBL(pExecuteObject);
#define CMD_CERROR 632
void COMMAND_CERROR(pExecuteObject);
#define CMD_EXTOPBO 633
void COMMAND_EXTOPBO(pExecuteObject);
#define CMD_FOR 634
void COMMAND_FOR(pExecuteObject);
#define CMD_ENVIRON 635
void COMMAND_ENVIRON(pExecuteObject);
#define CMD_EXTOPOE 636
void COMMAND_EXTOPOE(pExecuteObject);
#define CMD_EXTOPKJ 637
void COMMAND_EXTOPKJ(pExecuteObject);
#define CMD_EXTOPON 638
void COMMAND_EXTOPON(pExecuteObject);
#define CMD_CLOSEDIR 639
void COMMAND_CLOSEDIR(pExecuteObject);
#define CMD_LOC 640
void COMMAND_LOC(pExecuteObject);
#define CMD_EXTOPKN 641
void COMMAND_EXTOPKN(pExecuteObject);
#define CMD_SUB 642
void COMMAND_SUB(pExecuteObject);
#define CMD_REF 643
void COMMAND_REF(pExecuteObject);
#define CMD_EXTOPDH 644
void COMMAND_EXTOPDH(pExecuteObject);
#define CMD_EXTOPNK 645
void COMMAND_EXTOPNK(pExecuteObject);
#define CMD_ONERRORRESUMELABEL 646
void COMMAND_ONERRORRESUMELABEL(pExecuteObject);
#define CMD_EXTOPKL 647
void COMMAND_EXTOPKL(pExecuteObject);
#define CMD_EXTOPAC 648
void COMMAND_EXTOPAC(pExecuteObject);
#define CMD_EXTOPDC 649
void COMMAND_EXTOPDC(pExecuteObject);
#define CMD_EXTOPLM 650
void COMMAND_EXTOPLM(pExecuteObject);
#define CMD_EXTOPAP 651
void COMMAND_EXTOPAP(pExecuteObject);
#define CMD_EXTOPFN 652
void COMMAND_EXTOPFN(pExecuteObject);
#define CMD_EXTOPGP 653
void COMMAND_EXTOPGP(pExecuteObject);
#define CMD_EXTOPFG 654
void COMMAND_EXTOPFG(pExecuteObject);
#define CMD_FORSTEP 655
void COMMAND_FORSTEP(pExecuteObject);
#define CMD_WEND 656
void COMMAND_WEND(pExecuteObject);
#define CMD_ACOSECANT 657
void COMMAND_ACOSECANT(pExecuteObject);
#define CMD_CREATEPROCESS 658
void COMMAND_CREATEPROCESS(pExecuteObject);
#define CMD_ACOS 659
void COMMAND_ACOS(pExecuteObject);
#define CMD_EXTOPIJ 660
void COMMAND_EXTOPIJ(pExecuteObject);
#define CMD_EXTOPEF 661
void COMMAND_EXTOPEF(pExecuteObject);
#define CMD_EXTOPOC 662
void COMMAND_EXTOPOC(pExecuteObject);
#define CMD_ATN 663
void COMMAND_ATN(pExecuteObject);
#define CMD_LBOUND 664
void COMMAND_LBOUND(pExecuteObject);
#define CMD_EXTOPNL 665
void COMMAND_EXTOPNL(pExecuteObject);
#define CMD_EXTOPPE 666
void COMMAND_EXTOPPE(pExecuteObject);
#define CMD_MID 667
void COMMAND_MID(pExecuteObject);
#define CMD_CLOSE 668
void COMMAND_CLOSE(pExecuteObject);
#define CMD_EXTOPQN 669
void COMMAND_EXTOPQN(pExecuteObject);
#define CMD_RESET 670
void COMMAND_RESET(pExecuteObject);
#define CMD_EXTOPOD 671
void COMMAND_EXTOPOD(pExecuteObject);
#define CMD_EXTOPLO 672
void COMMAND_EXTOPLO(pExecuteObject);
#define CMD_EXTOPGD 673
void COMMAND_EXTOPGD(pExecuteObject);
#define CMD_EXTOPCP 674
void COMMAND_EXTOPCP(pExecuteObject);
#define CMD_SPLIT 675
void COMMAND_SPLIT(pExecuteObject);
#define CMD_EXTOPBJ 676
void COMMAND_EXTOPBJ(pExecuteObject);
#define CMD_COTAN 677
void COMMAND_COTAN(pExecuteObject);
#define CMD_MKD 678
void COMMAND_MKD(pExecuteObject);
#define CMD_EXTOPQK 679
void COMMAND_EXTOPQK(pExecuteObject);
#define CMD_POW 680
void COMMAND_POW(pExecuteObject);
#define CMD_LOCAL 879
#define CMD_EXTOPAE 681
void COMMAND_EXTOPAE(pExecuteObject);
#define CMD_OPTIONF 682
void COMMAND_OPTIONF(pExecuteObject);
#define CMD_END 683
void COMMAND_END(pExecuteObject);
#define CMD_LE 684
void COMMAND_LE(pExecuteObject);
#define CMD_LTRIM 685
void COMMAND_LTRIM(pExecuteObject);
#define CMD_EXTOPCN 686
void COMMAND_EXTOPCN(pExecuteObject);
#define CMD_PACK 687
void COMMAND_PACK(pExecuteObject);
#define CMD_EXTOPPP 688
void COMMAND_EXTOPPP(pExecuteObject);
#define CMD_HSIN 689
void COMMAND_HSIN(pExecuteObject);
#define CMD_ISREG 690
void COMMAND_ISREG(pExecuteObject);
#define CMD_EXTOPQP 691
void COMMAND_EXTOPQP(pExecuteObject);
#define CMD_INPUTFUN 692
void COMMAND_INPUTFUN(pExecuteObject);
#define CMD_LETS 693
void COMMAND_LETS(pExecuteObject);
#define CMD_PAUSE 694
void COMMAND_PAUSE(pExecuteObject);
#define CMD_CHR 695
void COMMAND_CHR(pExecuteObject);
#define CMD_EXTOPJH 696
void COMMAND_EXTOPJH(pExecuteObject);
#define CMD_RIGHT 697
void COMMAND_RIGHT(pExecuteObject);
#define CMD_NAME 698
void COMMAND_NAME(pExecuteObject);
#define CMD_EXTOPKD 699
void COMMAND_EXTOPKD(pExecuteObject);
#define CMD_EXTOPEJ 700
void COMMAND_EXTOPEJ(pExecuteObject);
#define CMD_NLABEL 880
#define CMD_ELSE 701
void COMMAND_ELSE(pExecuteObject);
#define CMD_SPLITAQ 702
void COMMAND_SPLITAQ(pExecuteObject);
#define CMD_CONST 881
#define CMD_EXTOPJG 703
void COMMAND_EXTOPJG(pExecuteObject);
#define CMD_EXTOPMF 704
void COMMAND_EXTOPMF(pExecuteObject);
#define CMD_SUBARG 705
void COMMAND_SUBARG(pExecuteObject);
#define CMD_FORMATDATE 706
void COMMAND_FORMATDATE(pExecuteObject);
#define CMD_CBYVAL 707
void COMMAND_CBYVAL(pExecuteObject);
#define CMD_POP 708
void COMMAND_POP(pExecuteObject);
#define CMD_EXTOPKF 709
void COMMAND_EXTOPKF(pExecuteObject);
#define CMD_INSTR 710
void COMMAND_INSTR(pExecuteObject);
#define CMD_CVI 711
void COMMAND_CVI(pExecuteObject);
#define CMD_ERROR 712
void COMMAND_ERROR(pExecuteObject);
#define CMD_EXTOPPN 713
void COMMAND_EXTOPPN(pExecuteObject);
#define CMD_RLOCK 714
void COMMAND_RLOCK(pExecuteObject);
#define CMD_INT 715
void COMMAND_INT(pExecuteObject);
#define CMD_EXTOPDQ 716
void COMMAND_EXTOPDQ(pExecuteObject);
#define CMD_EXTOPAM 717
void COMMAND_EXTOPAM(pExecuteObject);
#define CMD_EXTOPAH 718
void COMMAND_EXTOPAH(pExecuteObject);
#define CMD_AND 719
void COMMAND_AND(pExecuteObject);
#define CMD_TXTMI 720
void COMMAND_TXTMI(pExecuteObject);
#define CMD_REPLACE 721
void COMMAND_REPLACE(pExecuteObject);
#define CMD_EXTOPQO 722
void COMMAND_EXTOPQO(pExecuteObject);
#define CMD_EXTOPLG 723
void COMMAND_EXTOPLG(pExecuteObject);
#define CMD_EXTOPFP 724
void COMMAND_EXTOPFP(pExecuteObject);
#define CMD_BIN 725
void COMMAND_BIN(pExecuteObject);
#define CMD_EXTOPLF 726
void COMMAND_EXTOPLF(pExecuteObject);
#define CMD_EXTOPMD 727
void COMMAND_EXTOPMD(pExecuteObject);
#define CMD_EXTOPNO 728
void COMMAND_EXTOPNO(pExecuteObject);
#define CMD_FORK 729
void COMMAND_FORK(pExecuteObject);
#define CMD_SIN 730
void COMMAND_SIN(pExecuteObject);
#define CMD_EXTOPPJ 731
void COMMAND_EXTOPPJ(pExecuteObject);
#define CMD_CVS 732
void COMMAND_CVS(pExecuteObject);
#define CMD_EXTOPLI 733
void COMMAND_EXTOPLI(pExecuteObject);
#define CMD_EXTOPPH 734
void COMMAND_EXTOPPH(pExecuteObject);
#define CMD_EXTOPGM 735
void COMMAND_EXTOPGM(pExecuteObject);
#define CMD_RESUMELABEL 736
void COMMAND_RESUMELABEL(pExecuteObject);
#define CMD_EXTOPOF 737
void COMMAND_EXTOPOF(pExecuteObject);
#define CMD_LOOP 738
void COMMAND_LOOP(pExecuteObject);
#define CMD_BINMO 739
void COMMAND_BINMO(pExecuteObject);
#define CMD_STRING 740
void COMMAND_STRING(pExecuteObject);
#define CMD_EXTOPCM 741
void COMMAND_EXTOPCM(pExecuteObject);
#define CMD_EXTOPOK 742
void COMMAND_EXTOPOK(pExecuteObject);
#define CMD_EXTOPCK 743
void COMMAND_EXTOPCK(pExecuteObject);
#define CMD_EXTOPIO 744
void COMMAND_EXTOPIO(pExecuteObject);
#define CMD_RESETDIR 745
void COMMAND_RESETDIR(pExecuteObject);
#define CMD_TRUE 746
void COMMAND_TRUE(pExecuteObject);
#define CMD_ADDDAY 747
void COMMAND_ADDDAY(pExecuteObject);
#define CMD_EODFUN 748
void COMMAND_EODFUN(pExecuteObject);
#define CMD_WAITPID 749
void COMMAND_WAITPID(pExecuteObject);
#define CMD_MKDIR 750
void COMMAND_MKDIR(pExecuteObject);
#define CMD_STOP 751
void COMMAND_STOP(pExecuteObject);
#define CMD_OR 752
void COMMAND_OR(pExecuteObject);
#define CMD_EXTOPFD 753
void COMMAND_EXTOPFD(pExecuteObject);
#define CMD_MODULE 882
#define CMD_NE 754
void COMMAND_NE(pExecuteObject);
#define CMD_EXTOPML 755
void COMMAND_EXTOPML(pExecuteObject);
#define CMD_EXTOPFK 756
void COMMAND_EXTOPFK(pExecuteObject);
#define CMD_EXTOPIL 757
void COMMAND_EXTOPIL(pExecuteObject);
#define CMD_EXTOPGL 758
void COMMAND_EXTOPGL(pExecuteObject);
#define CMD_EXTOPMP 759
void COMMAND_EXTOPMP(pExecuteObject);
#define CMD_EXTOPNE 760
void COMMAND_EXTOPNE(pExecuteObject);
#define CMD_EXTOPPM 761
void COMMAND_EXTOPPM(pExecuteObject);
#define CMD_MIN 762
void COMMAND_MIN(pExecuteObject);
#define CMD_EMPTY 883
#define CMD_EXTERNAM 763
void COMMAND_EXTERNAM(pExecuteObject);
#define CMD_FPRINTNL 764
void COMMAND_FPRINTNL(pExecuteObject);
#define CMD_BINMF 765
void COMMAND_BINMF(pExecuteObject);
#define CMD_EXTOPHF 766
void COMMAND_EXTOPHF(pExecuteObject);
#define CMD_EXTOPGH 767
void COMMAND_EXTOPGH(pExecuteObject);
#define CMD_EXTOPCF 768
void COMMAND_EXTOPCF(pExecuteObject);
#define CMD_EXTOPEP 769
void COMMAND_EXTOPEP(pExecuteObject);
#define CMD_EXTOPJD 770
void COMMAND_EXTOPJD(pExecuteObject);
#define CMD_SPLITA 771
void COMMAND_SPLITA(pExecuteObject);
#define CMD_PRINTNL 772
void COMMAND_PRINTNL(pExecuteObject);
#define CMD_EXTOPFQ 773
void COMMAND_EXTOPFQ(pExecuteObject);
#define CMD_EXTOPK 774
void COMMAND_EXTOPK(pExecuteObject);
#define CMD_EXTOPOP 775
void COMMAND_EXTOPOP(pExecuteObject);
#define CMD_INSTRREV 776
void COMMAND_INSTRREV(pExecuteObject);
#define CMD_EXTOPPC 777
void COMMAND_EXTOPPC(pExecuteObject);
#define CMD_EXTOPJE 778
void COMMAND_EXTOPJE(pExecuteObject);
#define CMD_PRAGMA 884
#define CMD_LINPUTF 779
void COMMAND_LINPUTF(pExecuteObject);
#define CMD_HOSTNAME 780
void COMMAND_HOSTNAME(pExecuteObject);
#define CMD_NEXTFILE 781
void COMMAND_NEXTFILE(pExecuteObject);
#define CMD_FTACCESS 782
void COMMAND_FTACCESS(pExecuteObject);
#define CMD_OPENDIR 783
void COMMAND_OPENDIR(pExecuteObject);
#define CMD_EXTOPQE 784
void COMMAND_EXTOPQE(pExecuteObject);
#define CMD_EXTOPBP 785
void COMMAND_EXTOPBP(pExecuteObject);
#define CMD_EXTOPAQ 786
void COMMAND_EXTOPAQ(pExecuteObject);
#define CMD_EXTOPIK 787
void COMMAND_EXTOPIK(pExecuteObject);
#define CMD_EXTOPNF 788
void COMMAND_EXTOPNF(pExecuteObject);
#define CMD_LEFT 789
void COMMAND_LEFT(pExecuteObject);
#define CMD_TXTMF 790
void COMMAND_TXTMF(pExecuteObject);
#define CMD_ISSTRING 791
void COMMAND_ISSTRING(pExecuteObject);
#define CMD_NEXT 792
void COMMAND_NEXT(pExecuteObject);
#define CMD_EXTOPAK 793
void COMMAND_EXTOPAK(pExecuteObject);
#define CMD_EXTOPJQ 794
void COMMAND_EXTOPJQ(pExecuteObject);
#define CMD_FLET 795
void COMMAND_FLET(pExecuteObject);
#define CMD_EOFFUN 796
void COMMAND_EOFFUN(pExecuteObject);
#define CMD_TYPE 797
void COMMAND_TYPE(pExecuteObject);
#define CMD_MININT 798
void COMMAND_MININT(pExecuteObject);
#define CMD_LOCAL2GM 799
void COMMAND_LOCAL2GM(pExecuteObject);
#define CMD_EXTOPGE 800
void COMMAND_EXTOPGE(pExecuteObject);
#define CMD_EXTOPDK 801
void COMMAND_EXTOPDK(pExecuteObject);
#define CMD_DELETE 802
void COMMAND_DELETE(pExecuteObject);
#define CMD_EXTOPOJ 803
void COMMAND_EXTOPOJ(pExecuteObject);
#define CMD_ATAN 804
void COMMAND_ATAN(pExecuteObject);
#define CMD_ACTAN 805
void COMMAND_ACTAN(pExecuteObject);
#define CMD_HOUR 806
void COMMAND_HOUR(pExecuteObject);
#define CMD_EXTOPDI 807
void COMMAND_EXTOPDI(pExecuteObject);
#define CMD_EXTOPOG 808
void COMMAND_EXTOPOG(pExecuteObject);
#define CMD_EXTOPQM 809
void COMMAND_EXTOPQM(pExecuteObject);
#define CMD_EXTOPAJ 810
void COMMAND_EXTOPAJ(pExecuteObject);
#define CMD_EXTOPEE 811
void COMMAND_EXTOPEE(pExecuteObject);
#define CMD_EXTOPEH 812
void COMMAND_EXTOPEH(pExecuteObject);
#define CMD_EXTOPPQ 813
void COMMAND_EXTOPPQ(pExecuteObject);
#define CMD_ADDRESSF 814
void COMMAND_ADDRESSF(pExecuteObject);
#define CMD_EXTOPLQ 815
void COMMAND_EXTOPLQ(pExecuteObject);
#define CMD_LETD 816
void COMMAND_LETD(pExecuteObject);
#define CMD_GMTIME 817
void COMMAND_GMTIME(pExecuteObject);
#define CMD_ENDIF 818
void COMMAND_ENDIF(pExecuteObject);
#define CMD_EXTOPDN 819
void COMMAND_EXTOPDN(pExecuteObject);
#define CMD_TIMEVALUE 820
void COMMAND_TIMEVALUE(pExecuteObject);
#define CMD_HCOSECANT 821
void COMMAND_HCOSECANT(pExecuteObject);
#define CMD_ADDSECOND 822
void COMMAND_ADDSECOND(pExecuteObject);
#define CMD_CVD 823
void COMMAND_CVD(pExecuteObject);
#define CMD_HCOS 824
void COMMAND_HCOS(pExecuteObject);
#define CMD_GLOBAL 885
#define CMD_FTCREATED 825
void COMMAND_FTCREATED(pExecuteObject);
#define CMD_EXTOPBM 826
void COMMAND_EXTOPBM(pExecuteObject);
#define CMD_EXTOPKO 827
void COMMAND_EXTOPKO(pExecuteObject);
#define CMD_EXTOPQI 828
void COMMAND_EXTOPQI(pExecuteObject);
#define CMD_EXTOPIF 829
void COMMAND_EXTOPIF(pExecuteObject);
#define CMD_OCT 830
void COMMAND_OCT(pExecuteObject);
#define CMD_WHILE 831
void COMMAND_WHILE(pExecuteObject);
#define CMD_IF 832
void COMMAND_IF(pExecuteObject);
#define CMD_EXTOPKH 833
void COMMAND_EXTOPKH(pExecuteObject);
#define CMD_EXTOPFI 834
void COMMAND_EXTOPFI(pExecuteObject);
#define CMD_MKL 835
void COMMAND_MKL(pExecuteObject);
#define CMD_DAY 836
void COMMAND_DAY(pExecuteObject);
#define CMD_EXTOPNG 837
void COMMAND_EXTOPNG(pExecuteObject);
#define CMD_EXTOPBE 838
void COMMAND_EXTOPBE(pExecuteObject);
#define CMD_EXTOPLH 839
void COMMAND_EXTOPLH(pExecuteObject);
#define CMD_EXTOPED 840
void COMMAND_EXTOPED(pExecuteObject);
#define CMD_GM2LOCAL 841
void COMMAND_GM2LOCAL(pExecuteObject);
#define CMD_SPACE 842
void COMMAND_SPACE(pExecuteObject);
#define CMD_EXTOPMH 843
void COMMAND_EXTOPMH(pExecuteObject);
#define CMD_EXTOPAO 844
void COMMAND_EXTOPAO(pExecuteObject);
#define CMD_EXTOPDM 845
void COMMAND_EXTOPDM(pExecuteObject);
#define CMD_EXTOPMJ 846
void COMMAND_EXTOPMJ(pExecuteObject);
#define CMD_EXTOPEL 847
void COMMAND_EXTOPEL(pExecuteObject);
#define CMD_TXTMO 848
void COMMAND_TXTMO(pExecuteObject);
#define CMD_MINUS 849
void COMMAND_MINUS(pExecuteObject);
#define CMD_EXTOPDJ 850
void COMMAND_EXTOPDJ(pExecuteObject);
#define CMD_EXTOPGI 851
void COMMAND_EXTOPGI(pExecuteObject);
#define CMD_LETI 852
void COMMAND_LETI(pExecuteObject);
#define CMD_EXTOPKM 853
void COMMAND_EXTOPKM(pExecuteObject);
#define CMD_EXTOPHE 854
void COMMAND_EXTOPHE(pExecuteObject);
#define CMD_MAXINT 855
void COMMAND_MAXINT(pExecuteObject);
#define CMD_UCASE 856
void COMMAND_UCASE(pExecuteObject);
#define CMD_EXTOPGO 857
void COMMAND_EXTOPGO(pExecuteObject);
#define CMD_FORMAT 858
void COMMAND_FORMAT(pExecuteObject);
#define CMD_EXTOPHK 859
void COMMAND_EXTOPHK(pExecuteObject);
#define CMD_EXTOPDD 860
void COMMAND_EXTOPDD(pExecuteObject);
#define CMD_EXTOPCQ 861
void COMMAND_EXTOPCQ(pExecuteObject);
#define CMD_EXTOPQD 862
void COMMAND_EXTOPQD(pExecuteObject);
#define CMD_EXTOPHH 863
void COMMAND_EXTOPHH(pExecuteObject);
#define CMD_LOOPUNTIL 864
void COMMAND_LOOPUNTIL(pExecuteObject);
#define CMD_EXTOPFL 865
void COMMAND_EXTOPFL(pExecuteObject);
#define CMD_EXTOPND 866
void COMMAND_EXTOPND(pExecuteObject);
#define CMD_YEAR 867
void COMMAND_YEAR(pExecuteObject);
#define CMD_ENDSUB 868
void COMMAND_ENDSUB(pExecuteObject);
#define CMD_FILELEN 869
void COMMAND_FILELEN(pExecuteObject);
#define CMD_CHOMP 870
void COMMAND_CHOMP(pExecuteObject);
#define CMD_EXTOPLL 871
void COMMAND_EXTOPLL(pExecuteObject);
#define CMD_EXTOPPK 872
void COMMAND_EXTOPPK(pExecuteObject);
#define CMD_REPEAT 873
void COMMAND_REPEAT(pExecuteObject);
#define CMD_EXTOPQH 874
void COMMAND_EXTOPQH(pExecuteObject);
#define KEYWORDCODE_ISINTEGER CMD_ISLONG
#define KEYWORDCODE_ISNUMERIC CMD_ISNUMERIC
#define KEYWORDCODE_ISDEFINED CMD_ISDEF
#define KEYWORDCODE_ACOSECANT CMD_ACOSECANT
#define KEYWORDCODE_HCOSECANT CMD_HCOSECANT
#define KEYWORDCODE_FILEOWNER CMD_FOWNER
#define KEYWORDCODE_TIMEVALUE CMD_TIMEVALUE
#define KEYWORDCODE_ADDMINUTE CMD_ADDMINUTE
#define KEYWORDCODE_ADDSECOND CMD_ADDSECOND
#define KEYWORDCODE_DIRECTORY 310
#define KEYWORDCODE_RANDOMIZE 342
#define KEYWORDCODE_ISSTRING CMD_ISSTRING
#define KEYWORDCODE_COSECANT CMD_COSECANT
#define KEYWORDCODE_INSTRREV CMD_INSTRREV
#define KEYWORDCODE_FREEFILE CMD_FREEFILE
#define KEYWORDCODE_NEXTFILE CMD_NEXTFILE
#define KEYWORDCODE_ENVIRONS CMD_ENVIRON
#define KEYWORDCODE_ADDMONTH CMD_ADDMONTH
#define KEYWORDCODE_HOSTNAME CMD_HOSTNAME
#define KEYWORDCODE_FILECOPY 328
#define KEYWORDCODE_TEXTMODE 335
#define KEYWORDCODE_TRUNCATE 321
#define KEYWORDCODE_CLOSEALL 316
#define KEYWORDCODE_FUNCTION 268
#define KEYWORDCODE_ISARRAY CMD_ISARRAY
#define KEYWORDCODE_ISUNDEF CMD_ISUNDEF
#define KEYWORDCODE_ISEMPTY CMD_ISEMPTY
#define KEYWORDCODE_ASECANT CMD_ASECANT
#define KEYWORDCODE_HSECANT CMD_HSECANT
#define KEYWORDCODE_STRINGS CMD_STRING
#define KEYWORDCODE_REPLACE CMD_REPLACE
#define KEYWORDCODE_FILELEN CMD_FILELEN
#define KEYWORDCODE_ENVIRON CMD_ENVIRON
#define KEYWORDCODE_COMMAND CMD_COMMANDF
#define KEYWORDCODE_ADDRESS CMD_ADDRESSF
#define KEYWORDCODE_WEEKDAY CMD_WDAY
#define KEYWORDCODE_YEARDAY CMD_YDAY
#define KEYWORDCODE_ADDYEAR CMD_ADDYEAR
#define KEYWORDCODE_ADDHOUR CMD_ADDHOUR
#define KEYWORDCODE_ADDWEEK CMD_ADDWEEK
#define KEYWORDCODE_EXECUTE CMD_CREATEPROCESSEX
#define KEYWORDCODE_WAITPID CMD_WAITPID
#define KEYWORDCODE_DECLARE 260
#define KEYWORDCODE_PATTERN 311
#define KEYWORDCODE_PRINTNL 266
#define KEYWORDCODE_DELTREE 326
#define KEYWORDCODE_BINMODE 333
#define KEYWORDCODE_SPLITAQ 336
#define KEYWORDCODE_MAXINT CMD_MAXINT
#define KEYWORDCODE_MININT CMD_MININT
#define KEYWORDCODE_STRING CMD_STRING
#define KEYWORDCODE_LBOUND CMD_LBOUND
#define KEYWORDCODE_UBOUND CMD_UBOUND
#define KEYWORDCODE_ISREAL CMD_ISDOUBLE
#define KEYWORDCODE_COTAN2 CMD_COTAN2
#define KEYWORDCODE_SECANT CMD_SECANT
#define KEYWORDCODE_UCASES CMD_UCASE
#define KEYWORDCODE_UPPERS CMD_UCASE
#define KEYWORDCODE_LCASES CMD_LCASE
#define KEYWORDCODE_LOWERS CMD_LCASE
#define KEYWORDCODE_LTRIMS CMD_LTRIM
#define KEYWORDCODE_RTRIMS CMD_RTRIM
#define KEYWORDCODE_RIGHTS CMD_RIGHT
#define KEYWORDCODE_SPACES CMD_SPACE
#define KEYWORDCODE_OPTION CMD_OPTIONF
#define KEYWORDCODE_ERRORS CMD_ERRORDOLLAR
#define KEYWORDCODE_ISFILE CMD_ISREG
#define KEYWORDCODE_CURDIR CMD_CURDIR
#define KEYWORDCODE_FORMAT CMD_FORMAT
#define KEYWORDCODE_GMTIME CMD_GMTIME
#define KEYWORDCODE_MINUTE CMD_MINUTE
#define KEYWORDCODE_ADDDAY CMD_ADDDAY
#define KEYWORDCODE_SYSTEM CMD_CREATEPROCESS
#define KEYWORDCODE_GLOBAL 263
#define KEYWORDCODE_OUTPUT 334
#define KEYWORDCODE_RETURN 285
#define KEYWORDCODE_UNPACK 341
#define KEYWORDCODE_SPLITA 339
#define KEYWORDCODE_ELSEIF 304
#define KEYWORDCODE_REWIND 318
#define KEYWORDCODE_RESUME 292
#define KEYWORDCODE_REGION 323
#define KEYWORDCODE_DELETE 327
#define KEYWORDCODE_REPEAT 299
#define KEYWORDCODE_MODULE 256
#define KEYWORDCODE_BYVAL CMD_BYVAL
#define KEYWORDCODE_FALSE CMD_FALSE
#define KEYWORDCODE_UNDEF CMD_UNDEF
#define KEYWORDCODE_ROUND CMD_ROUND
#define KEYWORDCODE_LOG10 CMD_LOG10
#define KEYWORDCODE_UCASE CMD_UCASE
#define KEYWORDCODE_LCASE CMD_LCASE
#define KEYWORDCODE_LTRIM CMD_LTRIM
#define KEYWORDCODE_RTRIM CMD_RTRIM
#define KEYWORDCODE_RIGHT CMD_RIGHT
#define KEYWORDCODE_SPACE CMD_SPACE
#define KEYWORDCODE_JOKER CMD_JOKER
#define KEYWORDCODE_CHOMP CMD_CHOMP
#define KEYWORDCODE_ACTAN CMD_ACTAN
#define KEYWORDCODE_COTAN CMD_COTAN
#define KEYWORDCODE_HCTAN CMD_HCTAN
#define KEYWORDCODE_UPPER CMD_UCASE
#define KEYWORDCODE_LOWER CMD_LCASE
#define KEYWORDCODE_TRIMS CMD_TRIM
#define KEYWORDCODE_LEFTS CMD_LEFT
#define KEYWORDCODE_INSTR CMD_INSTR
#define KEYWORDCODE_ERROR CMD_ERROR
#define KEYWORDCODE_INPUT CMD_INPUTFUN
#define KEYWORDCODE_MONTH CMD_MONTH
#define KEYWORDCODE_ICALL CMD_ICALLFUN
#define KEYWORDCODE_CRYPT CMD_FCRYPT
#define KEYWORDCODE_CONST 262
#define KEYWORDCODE_CLOSE 314
#define KEYWORDCODE_LOCAL 258
#define KEYWORDCODE_MKDIR 325
#define KEYWORDCODE_RESET 313
#define KEYWORDCODE_WHILE 294
#define KEYWORDCODE_QUOTE 338
#define KEYWORDCODE_GOSUB 284
#define KEYWORDCODE_UNTIL 297
#define KEYWORDCODE_ALIAS 348
#define KEYWORDCODE_PRINT 267
#define KEYWORDCODE_PAUSE 347
#define KEYWORDCODE_SPLIT 340
#define KEYWORDCODE_ELSIF 307
#define KEYWORDCODE_ENDIF 308
#define KEYWORDCODE_SLEEP 346
#define KEYWORDCODE_CHDIR 330
#define KEYWORDCODE_LIKE CMD_LIKEOP
#define KEYWORDCODE_ASIN CMD_ASIN
#define KEYWORDCODE_ACOS CMD_ACOS
#define KEYWORDCODE_EVEN CMD_EVEN
#define KEYWORDCODE_TRUE CMD_TRUE
#define KEYWORDCODE_CINT CMD_INT
#define KEYWORDCODE_FRAC CMD_FRAC
#define KEYWORDCODE_MKDS CMD_MKD
#define KEYWORDCODE_MKIS CMD_MKI
#define KEYWORDCODE_MKSS CMD_MKS
#define KEYWORDCODE_MKLS CMD_MKL
#define KEYWORDCODE_TRIM CMD_TRIM
#define KEYWORDCODE_LEFT CMD_LEFT
#define KEYWORDCODE_TYPE CMD_TYPE
#define KEYWORDCODE_ATAN CMD_ATAN
#define KEYWORDCODE_HCOS CMD_HCOS
#define KEYWORDCODE_HSIN CMD_HSIN
#define KEYWORDCODE_HTAN CMD_HTAN
#define KEYWORDCODE_TAN2 CMD_TAN2
#define KEYWORDCODE_MIDS CMD_MID
#define KEYWORDCODE_CHRS CMD_CHR
#define KEYWORDCODE_STRS CMD_STR
#define KEYWORDCODE_HEXS CMD_HEX
#define KEYWORDCODE_OCTS CMD_OCT
#define KEYWORDCODE_JOIN CMD_JOIN
#define KEYWORDCODE_IMAX CMD_IMAX
#define KEYWORDCODE_IMIN CMD_IMIN
#define KEYWORDCODE_PACK CMD_PACK
#define KEYWORDCODE_TIME CMD_NOW
#define KEYWORDCODE_YEAR CMD_YEAR
#define KEYWORDCODE_HOUR CMD_HOUR
#define KEYWORDCODE_CONF CMD_CONF
#define KEYWORDCODE_KILL CMD_KILL
#define KEYWORDCODE_FORK CMD_FORK
#define KEYWORDCODE_THEN 303
#define KEYWORDCODE_GOTO 281
#define KEYWORDCODE_FILE 332
#define KEYWORDCODE_CALL 271
#define KEYWORDCODE_SWAP 265
#define KEYWORDCODE_LOCK 322
#define KEYWORDCODE_ELIF 306
#define KEYWORDCODE_NEXT 293
#define KEYWORDCODE_ELSE 305
#define KEYWORDCODE_NULL 291
#define KEYWORDCODE_STEP 301
#define KEYWORDCODE_STOP 259
#define KEYWORDCODE_WILD 344
#define KEYWORDCODE_SEEK 317
#define KEYWORDCODE_EXIT 269
#define KEYWORDCODE_OPEN 309
#define KEYWORDCODE_WEND 295
#define KEYWORDCODE_LOOP 298
#define KEYWORDCODE_LINE 319
#define KEYWORDCODE_FROM 324
#define KEYWORDCODE_NAME 329
#define KEYWORDCODE_AND CMD_AND
#define KEYWORDCODE_XOR CMD_XOR
#define KEYWORDCODE_NOT CMD_NOT
#define KEYWORDCODE_SIN CMD_SIN
#define KEYWORDCODE_COS CMD_COS
#define KEYWORDCODE_SGN CMD_SGN
#define KEYWORDCODE_ODD CMD_ODD
#define KEYWORDCODE_GCD CMD_GCD
#define KEYWORDCODE_LCM CMD_LCM
#define KEYWORDCODE_SQR CMD_SQR
#define KEYWORDCODE_RND CMD_RND
#define KEYWORDCODE_ABS CMD_ABS
#define KEYWORDCODE_VAL CMD_VAL
#define KEYWORDCODE_FIX CMD_FIX
#define KEYWORDCODE_INT CMD_INT
#define KEYWORDCODE_CVD CMD_CVD
#define KEYWORDCODE_CVI CMD_CVI
#define KEYWORDCODE_CVL CMD_CVL
#define KEYWORDCODE_CVS CMD_CVS
#define KEYWORDCODE_MKD CMD_MKD
#define KEYWORDCODE_MKI CMD_MKI
#define KEYWORDCODE_MKS CMD_MKS
#define KEYWORDCODE_MKL CMD_MKL
#define KEYWORDCODE_LOG CMD_LOG
#define KEYWORDCODE_POW CMD_POW
#define KEYWORDCODE_EXP CMD_EXP
#define KEYWORDCODE_LEN CMD_LEN
#define KEYWORDCODE_ASC CMD_ASC
#define KEYWORDCODE_MID CMD_MID
#define KEYWORDCODE_CHR CMD_CHR
#define KEYWORDCODE_STR CMD_STR
#define KEYWORDCODE_HEX CMD_HEX
#define KEYWORDCODE_OCT CMD_OCT
#define KEYWORDCODE_ATN CMD_ATN
#define KEYWORDCODE_TAN CMD_TAN
#define KEYWORDCODE_BIN CMD_BIN
#define KEYWORDCODE_MAX CMD_MAX
#define KEYWORDCODE_MIN CMD_MIN
#define KEYWORDCODE_LOC CMD_LOC
#define KEYWORDCODE_LOF CMD_LOF
#define KEYWORDCODE_EOF CMD_EOFFUN
#define KEYWORDCODE_EOD CMD_EODFUN
#define KEYWORDCODE_NOW CMD_NOW
#define KEYWORDCODE_DAY CMD_DAY
#define KEYWORDCODE_SEC CMD_SEC
#define KEYWORDCODE_REF 280
#define KEYWORDCODE_LET 273
#define KEYWORDCODE_END 257
#define KEYWORDCODE_SUB 270
#define KEYWORDCODE_LIB 349
#define KEYWORDCODE_POP 286
#define KEYWORDCODE_SET 331
#define KEYWORDCODE_VAR 264
#define KEYWORDCODE_FOR 300
#define KEYWORDCODE_OR CMD_OR
#define KEYWORDCODE_PI CMD_PI
#define KEYWORDCODE_AS 312
#define KEYWORDCODE_TO 283
#define KEYWORDCODE_BY 337
#define KEYWORDCODE_NO 345
#define KEYWORDCODE_GO 282
#define KEYWORDCODE_DO 296
#define KEYWORDCODE_ON 289
#define KEYWORDCODE_IF 302
#define KEYWORDCODE_GMTIMETOLOCALTIME CMD_GM2LOCAL
#define KEYWORDCODE_LOCALTIMETOGMTIME CMD_LOCAL2GM
#define KEYWORDCODE_FILEACCESSTIME CMD_FTACCESS
#define KEYWORDCODE_FILEMODIFYTIME CMD_FTMODIFY
#define KEYWORDCODE_FILECREATETIME CMD_FTCREATED
#define KEYWORDCODE_STRREVERSES CMD_STRREVERSE
#define KEYWORDCODE_ISDIRECTORY CMD_ISDIR
#define KEYWORDCODE_STRREVERSE CMD_STRREVERSE
#define KEYWORDCODE_FILEEXISTS CMD_FILEXISTS
#define KEYWORDCODE_FORMATDATE CMD_FORMATDATE
#define KEYWORDCODE_FORMATTIME CMD_FORMATDATE
extern PredLConst PREDLCONSTS[];
extern unsigned long BINARIES[];
extern unsigned long UNARIES[];
extern BFun INTERNALFUNCTIONS[];
extern LineSyntax COMMANDS[];
extern LexNASymbol NASYMBOLS[];
extern LexNASymbol ASYMBOLS[];
extern LexNASymbol CSYMBOLS[];
extern char *COMMANDSYMBOLS[];
extern CommandFunctionType CommandFunction[];
#define END_EXEC 875
#ifdef __cplusplus
}
#endif
#endif
