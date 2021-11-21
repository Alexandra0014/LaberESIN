OPCIONS = -O0 -Wall -Wextra  -Wno-sign-compare -std=c++11 -ansi -g

program.exe: cambra.o laberint.o teseus.o dedalus.o
    g++ -o program.exe cambra.o laberint.o teseus.o dedalus.o -lesin
    rm *.o

cambra.o: cambra.cpp cambra.hpp cambra.rep paret.hpp
    g++ -c cambra.cpp $(OPCIONS)

laberint.o: laberint.cpp laberint.hpp laberint.rep cambra.cpp cambra.hpp cambra.rep
    g++ -c laberint.cpp $(OPCIONS)

teseus.o: teseus.cpp teseus.hpp laberint.cpp laberint.hpp laberint.rep
    g++ -c teseus.cpp $(OPCIONS)

dedalus.o: dedalus.cpp dedalus.hpp laberint.cpp laberint.hpp laberint.rep particio.t particio.rep particio.hpp
    g++ -c dedalus.cpp $(OPCIONS)

clean:
    rm *.o
    rm *.exe
    rm *.gch
