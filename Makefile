INC = -I/usr/include
BOOSTINC = -I/opt/local/include
BUILDDIR = bin

LIB = -L/usr/lib
BOOSTLIB = -L/opt/local/lib \
					 -lboost_system \
					 -lboost_thread \
					 -lboost_program_options
#CURLLIB = -lcurl -lssl -lcrypto -Wl,-weak-lldap -dynamic -Os -pipe -g0 -Wno-system-headers -Wl,-search_paths_first -Wl,-weak-lgssapi_krb5 -Wl,-weak-lkrb5 -Wl,-weak-lk5crypto -Wl,-weak-lcom_err -Wl,-weak-lresolv -lssl -lcrypto -lz -lz
CURLLIB = -lcurl -lssl -lcrypto
CXX = g++

OBJS = HttpClient.o QuoteData.o Quoter.o CliDisplay.o QuoteAppConfig.o
SRCS = $(OBJS,.o=.cpp)
HDRS = $(OBJS,.o=.h)
EXEC = qapp
EXECPATH = $(BUILDDIR)/qapp
INCLUDE = $(INC) $(BOOSTINC)
LIBS = $(LIB) $(BOOSTLIB) $(CURLLIB)
CFLAGS = 

all: $(EXECPATH)

run: $(EXECPATH)
	$<

$(EXECPATH): $(OBJS) main.cpp
	mkdir -p $(BUILDDIR)
	$(CXX) $(INCLUDE) $(CFLAGS) $(OBJS) main.cpp $(LIBS) -o $@

%.o: %.cpp %.h
	$(CXX) $(INCLUDE) $(CFLAGS) -c $<

clean:
	\rm $(OBJS)
	\rm $(EXECPATH)

