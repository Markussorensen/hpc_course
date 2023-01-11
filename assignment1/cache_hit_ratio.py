import numpy as np

mkn_l1_hits = 4746278755
mkn_l1_misses = 518902365
kmn_l1_hits = 3629566629
kmn_l1_misses = 374194118
mnk_l1_hits = 7097684386
mnk_l1_misses = 4306861229
nmk_l1_hits = 3512621359
nmk_l1_misses = 2045397590
nkm_l1_hits = 2283439013
nkm_l1_misses = 2199879392
knm_l1_hits = 2491910301
knm_l1_misses = 2142010900

#2.992	3.002	518902365	485002196	31494991	31529217	4746278755	0	matmult_mkn
mkn_l2_hits = 485002196
mkn_l2_misses = 31494991
#3.042	3.042	374194118	259399439	117289115	117175033	3629566629	0	matmult_kmn
kmn_l2_hits = 259399439
kmn_l2_misses = 117289115
#6.054	6.084	4306861229	3794083522	508342519	246270529	7097684386	0	matmult_mnk
mnk_l2_hits = 485002196
mnk_l2_misses = 31494991
#3.002	3.012	2045397590	2037639762	5997723	6007722	3512621359	0	matmult_nmk
nmk_l2_hits = 2037639762
nmk_l2_misses = 5997723
#3.212	3.212	2199879392	2070693133	130667888	130535885	2283439013	150086	matmult_nkm
nkm_l2_hits = 2070693133
nkm_l2_misses = 130667888
#3.372	3.372	2142010900	2008778806	127551589	127651186	2491910301	150221	matmult_knm
knm_l2_hits = 2008778806
knm_l2_misses = 127551589

mkn_l3_hits = 31494991
mkn_l3_misses = 0
kmn_l3_hits = 117175033
kmn_l3_misses = 0
mnk_l3_hits = 246270529
mnk_l3_misses = 0
nmk_l3_hits = 6007722
nmk_l3_misses = 0
nkm_l3_hits = 130535885
nkm_l3_misses = 150086
knm_l3_hits = 127651186
knm_l3_misses = 150221

mkn_l1_hitrate = mkn_l1_hits / (mkn_l1_hits + mkn_l1_misses)
mkn_l2_hitrate = mkn_l2_hits / (mkn_l2_hits + mkn_l2_misses)
mkn_l3_hitrate = mkn_l3_hits / (mkn_l3_hits + mkn_l3_misses)
kmn_l1_hitrate = kmn_l1_hits / (kmn_l1_hits + kmn_l1_misses)
kmn_l2_hitrate = kmn_l2_hits / (kmn_l2_hits + kmn_l2_misses)
kmn_l3_hitrate = kmn_l3_hits / (kmn_l3_hits + kmn_l3_misses)
mnk_l1_hitrate = mnk_l1_hits / (mnk_l1_hits + mnk_l1_misses)
mnk_l2_hitrate = mnk_l2_hits / (mnk_l2_hits + mnk_l2_misses)
mnk_l3_hitrate = mnk_l3_hits / (mnk_l3_hits + mnk_l3_misses)
nmk_l1_hitrate = nmk_l1_hits / (nmk_l1_hits + nmk_l1_misses)
nmk_l2_hitrate = nmk_l2_hits / (nmk_l2_hits + nmk_l2_misses)
nmk_l3_hitrate = nmk_l3_hits / (nmk_l3_hits + nmk_l3_misses)
nkm_l1_hitrate = nkm_l1_hits / (nkm_l1_hits + nkm_l1_misses)
nkm_l2_hitrate = nkm_l2_hits / (nkm_l2_hits + nkm_l2_misses)
nkm_l3_hitrate = nkm_l3_hits / (nkm_l3_hits + nkm_l3_misses)
knm_l1_hitrate = knm_l1_hits / (knm_l1_hits + knm_l1_misses)
knm_l2_hitrate = knm_l2_hits / (knm_l2_hits + knm_l2_misses)
knm_l3_hitrate = knm_l3_hits / (knm_l3_hits + knm_l3_misses)

print("mkn_l1_hitrate: ", mkn_l1_hitrate)
print("mkn_l2_hitrate: ", mkn_l2_hitrate)
print("mkn_l3_hitrate: ", mkn_l3_hitrate)
print("kmn_l1_hitrate: ", kmn_l1_hitrate)
print("kmn_l2_hitrate: ", kmn_l2_hitrate)
print("kmn_l3_hitrate: ", kmn_l3_hitrate)
print("mnk_l1_hitrate: ", mnk_l1_hitrate)
print("mnk_l2_hitrate: ", mnk_l2_hitrate)
print("mnk_l3_hitrate: ", mnk_l3_hitrate)
print("nmk_l1_hitrate: ", nmk_l1_hitrate)
print("nmk_l2_hitrate: ", nmk_l2_hitrate)
print("nmk_l3_hitrate: ", nmk_l3_hitrate)
print("nkm_l1_hitrate: ", nkm_l1_hitrate)
print("nkm_l2_hitrate: ", nkm_l2_hitrate)
print("nkm_l3_hitrate: ", nkm_l3_hitrate)
print("knm_l1_hitrate: ", knm_l1_hitrate)
print("knm_l2_hitrate: ", knm_l2_hitrate)
print("knm_l3_hitrate: ", knm_l3_hitrate)

#3.052	3.052	8793794232	57592769	52832126	1502756	1501645	0	<Total>
lib_l1_hits = 8793794232
lib_l1_misses = 57592769
lib_l2_hits = 52832126
lib_l2_misses = 1502756
lib_l3_hits = 1501645
lib_l3_misses = 0

lib_l1_hitrate = lib_l1_hits / (lib_l1_hits + lib_l1_misses)
lib_l2_hitrate = lib_l2_hits / (lib_l2_hits + lib_l2_misses)
lib_l3_hitrate = lib_l3_hits / (lib_l3_hits + lib_l3_misses)

print("lib_l1_hitrate: ", lib_l1_hitrate)
print("lib_l2_hitrate: ", lib_l2_hitrate)
print("lib_l3_hitrate: ", lib_l3_hitrate)


