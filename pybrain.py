l=[0 for x in range(20)]
p=0
loops=[]
def printMEM():
        global l
        global p
        space=148*'='
        print(space)
        print(11*" ",end='')
        for j in l:
                print('|','%3d'%j,'|',sep='',end=' ')
        print()
        print(space)
        print(((p)*6+14)*' ','^',sep='')
        print(((p)*6+14)*' ','|',sep='')

def looper(s,start,end):
        global loops
        global l
        global p
        if not len(s[start:end+1])>2:
                printMEM()
                return
        while(l[p]!=0):
                passer=0
                for i in range(start+1,end):
                        if passer>0:
                                passer-=1
                                continue
                        for j in loops:
                                if i==j[0] and j[1]<end and j[0]>start:
                                        passer+=j[1]-j[0]
                                        looper(s,j[0],j[1])
                                elif j[0]>end:
                                        break
                                else:
                                        brain(s[i])
def brain(s):
        global p
        global l
        length=len(s)
        for i in range(length):
                if s[i]==',':
                        print("Input:",end="")
                        while(1):
                                inp=input()
                                if len(inp)==1:
                                        l[p]=ord(inp)
                                        break
                                else:
                                        print("Enter any single character value")
                elif s[i]=='.':
                        print(l[p])

                elif s[i]=='>':
                        p+=1
                        if p>19:
                                p=0
                elif s[i]=='<':
                        p-=1
                        if p<0:
                                p=19
                elif s[i]=='+':
                        l[p]+=1
                        if l[p]>255:
                                l[p]=0
                elif s[i]=='-':
                        l[p]-=1
                        if l[p]<0:
                                l[p]=255
print("Welcome to BrainFuck interpreter power by Python written by Shubham & Surendar..!")
print("Memory of 20 have been given,run in full screen to better visualization")
print("type 'exit' to exit")

while(1):
        s=input()
        if s=='exit':
                break
        if '[' in s and ']' in s:
                open_=[-1 for x  in range(s.count(']'))]
                close_=[-1 for x in range(s.count('['))]
                last=-1
                loops=[]
                length=len(s)
                for i in range(length):
                        if s[i]=='[':
                                last+=1
                                open_[last]=i
                        if s[i]==']':
                                loops.append([open_[last],i])
                                open_[last]=-1
                                last-=1
                loops=sorted(loops)
                if open_!=close_:
                        print("Mismatched paraenthesis..")
                        continue
                loop_start=0
                main_loop=[loops[0]]
                start=loops[0][0]
                end=loops[0][1]
                for j in loops:
                        if j[0]>start and j[1]>end:
                                main_loop.append(j)
                                start=j[0]
                                end=j[1]
                start=0
                for i in main_loop:
                        t=s[start:i[0]]
                        if t!='':
                                if t[0]!='[':
                                        brain(t)
                                        printMEM()
                                else:
                                        looper(s,start,i[0])
                                        printMEM()
                                start=i[0]
                        t=s[start:i[1]+1]
                        if t[0]!='[':
                                brain(t)
                                printMEM()
                        else:
                                looper(s,start,i[1])
                                printMEM()
                        start=i[1]+1
                t=s[start:length]
                if t!='':
                        brain(t)
                        printMEM()
        else:
                brain(s)
                printMEM()
