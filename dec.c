#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ROWS 500
#define COLUMNS 10

typedef struct attrib{
	int count;
	char* name;
};

typedef struct collect_attrib{
	attrib attribs;
};

typedef struct decision{
	int rows;
	int cols;
	double entropy;
	char[][] matrix;
	collect_attrib colattrs;
}

typedef struct tree{
	sharp root;
	int depth;
}

typedef struct sharp
{
	decision dec;
	sharp* pointers;
}
int searchAttrib(string str)
{
	for(int i=0;i<attribs.size();i++){
		if(attribs[i].name.compare(str)==0) return i;
	}
	return -1;
}
void processAttrib(string str)
{
	int pos=searchAttrib(str);
	if(pos==-1){
		attribs.resize(((int) attribs.size())+1);
		attribs[((int)attribs.size())-1].name=name;
		attribs[((int)attribs.size())-1].count++;
	}
	else{
		attribs[pos].count++;
	}
}

void printDec(decison d)
{
	for(int i=0;i<d.matrix.size();i++){
		for(j=0;j<d.matrix.size();j++){
			printf(matrix[i][j],"|");
		}
		printf("\n");
	}
}

decision withdrawAttribute(int col, char* name, int count)
{
	decision newdec(colattrs.size()-1);
	newdec.matrix.resize(count);
	newdec.rows=count;
	for(int i=0;i<newdec.rows;i++){
		newdec.matrix[i].resize(newdec.colattrs.size());
	}
	newdec.cols=newdec.colattrs.size();

	int tempi;
	for(int i=0;i<rows;i++){
		int oldj=0;
		if(matrix[i][col]=name){
			for(int j=0;j<newdec.cols;j++){
				if(j==col) oldj++;
				newdec.matrix[tempi][j]=matrix[i][oldj];
				oldj++;
			}
			tempi++;
		}
	}
	return newdec;
} 

void mountfile(char* file)
{
	matrix.resize(rows);
	for(int i=0;i<rows;i++){
		matrix[i].resize(columns);
	}
	rows=ROWS;
	cols=COLUMNS;
	FILE *fp;
	fp=fopen("adult.txt","r");
	for(int i=0;i<ROWS;i++){
		char* line;
		getline(fp,line);
		
		int x;
		int y=line.find(',',x);

		for (int j=0;j<COLUMNS;j++){
			matrix[i][j]=line.substr(x,y-x);
			x=y+1;
			y=line.find(',',x);
		}
	}
}

void accountProb()
{
	for(int i=0;i<cols;i++){
		for(j=0;j<rows;j++){
			collect_attrib[i].processAttrib(matrix[j][i]);
		}
	}
}

void calculateEntropy()
{
	accountProb();
	double Entropy=0;
	for(int i=0;i<collect_attrib[collect_attrib.size()-1].attribs.size();i++){
		attrib *tempAttrib=&collect_attrib[collect_attrib.size()-1].attribs[i];
		double quotient = (double)(tempAttrib->count)/matrix.size();
		Entropy += -(quotient*(log2(quotient)));
	}
	entropy=Entropy;
}

double calculateGainColumn(int col)
{
	double gain = entropy;
	for(int i=0;i<collect_attrib[col].attribs.size();i++){
		decision dec(collect_attrib.size());
		attrib *tempAttrib=&collect_attrib[col].attribs[i];
		dec.matrix.resize(tempAttrib->count);
		dec.rows=tempAttrib->count;
		for(j=0;j<tempAttrib->count;j++){
			dec.matrix[j].resize(cols);
		}
		dec.cols=cols;
		int x=0;
		for(int j=0;j<rows;j++){
			if(matrix[j][col]=tempAttrib->name){
				dec.matrix[x++]=matrix[j];
			}
		}
		dec.calculateEntropy();
		gain-=((double)tempAttrib->count/matrix.size())*(dec.entropy);
	}
	return gain;
}

void constructor_tree(int rows, int cols, char *file)
{
	sharp rootfile;
	rootfile.dec.mountfile(file);
	root=constructor_sharp();
	root=rootfile.id3();
	depth=0;
}

sharp* id3()
{
	if(dec.cols==1){
		printf(dec.matrix[0][0],"\n");
		return NULL;
	}
	dec.calculateEntropy();
	int colpartial=0;
	double gainpartial=0;
	for(int i=0;i<(dec.matrix[0].size()-1);i++){
		double gain = dec.calculateGainColumn(i);
		if(gain > gainpartial){
			colpartial=i;
			gainpartial=gain;
		}
	}

	collect_attrib* collect=&dec.collect_attrib[colpartial];
	pointers.resize(collect->attribs.size());
	for(int i=0;i<pointers.size();i++){
		sharp sh;
		sh.dec=dec.withdrawAttribute(colpartial,collect->attribs[i].name,collect->attribs[i].count)
		pointers[i]=constructor_sharp();
		pointers[i]=sh.id3();
	}
	return sh;
}


int main()
{
    int main (int argc, char *argv[]) {
        printf("Oblivious Distributed ID3\n");
        printf("================================\n");
        
        if (argc == 4) {
            const char *remote_host = strtok(argv[1], ":");
            const char *port = strtok(NULL, ":");
            ProtocolDesc pd;
            ProtocolIO *mul = malloc(sizeof(ProtocolIO));
            int currentParty;
            
            printf("Connecting to %s on port %s .. \n", remote_host, port);
            
            if(argv[2][0] == '1') {
                if(protocolAcceptTcp2P(&pd,port)!=0) {
                    printf("TCP accept from %s failed\n", remote_host);
                    exit(1);
                }
            }
            else {
                if(protocolConnectTcp2P(&pd,remote_host,port)!=0) {
                    printf("TCP connect to %s failed\n", remote_host);
                    exit(1);
                }
            }
            printf("Establishing parties...\n");
            currentParty = (argv[2][0] =='1'?1:2);
            setCurrentParty(&pd, currentParty);
            mul->data = atoi(argv[3]);
            
            printf("Executing Yao's Protocol...\n");
            execYaoProtocol(&pd, oblivMul, mul);
            cleanupProtocol(&pd);
            
            printf("Oblivious ID3 produced: %d\n", mul->result);
            free(mul);
        }
        else {
            printf("Usage: %s <hostname:port> <1|2> <data>  \n"
                   "\tHostname usage:\n"
                   "\tlocal -> 'localhost' remote -> IP address or DNS name\n", argv[0]);
        }
        
        time_t start, end;
        start=clock();
        tree tr(rows, columns, "adult.data");
        end=clock();
        printf("Time required for execution:" (end - start)/CLOCKS_PER_SEC,"seconds");
        return 0;

}
