man(adam).
man(peter).
man(paul).
man(jim).
man(bob).
man(pat).
man(tom).
woman(marry).
woman(eve).
woman(pam).
woman(liz).
woman(ann).
parent(adam,peter).
parent(eve,peter).
parent(adam,paul).
parent(marry,paul).
% parent(pam,bob).
parent(tom,bob).
parent(tom,liz).
parent(bob,ann).
parent(bob,pat).
parent(pat,jim).
father(F,C):-man(F),parent(F,C).
mother(M,C):-woman(M),parent(M,C).
is_father(F):-father(F,_). % Anonymous variable
is_mother(M):-mother(M,_). % Anonymous variable
son(S,P):-man(S),parent(P,S). 
daughter(D,P):-woman(D),parent(P,D). 
siblings(A,B):-parent(P,A),parent(P,B),A\=B. % siblings have at least one common parent 
					     % the test A\=B preserves that siblings are different persons 
full_siblings(A,B):- parent(F,A),parent(F,B),parent(M,A),parent(M,B),A\=B,F\=M.
              % full siblings have common parents (both)
              % the test F\=M preserves that full siblings have two different parents (father and mother, naturally)
full_siblings2(A,B):- father(F,A),father(F,B),mother(M,A),mother(M,B),A\=B.
              % another solution to "full siblings problem" that uses relations father and mother
uncle(U,N):-man(U),siblings(U,P),parent(P,N).
aunt(A,N):-woman(A),siblings(A,P),parent(P,N).
grand_parent(G,N):-parent(G,X),parent(X,N).