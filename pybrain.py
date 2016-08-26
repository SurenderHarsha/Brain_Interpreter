l=[0 for x in range(20)]
p=0
space=148*'='
while(1):
        s=input()
        if s=='exit':                   #type exit to break
                break
        passer=0
        length=len(s)
        for i in range(length):
                if passer>0:
                        passer-=1
                        continue
                if s[i]==',':
                        print("Input:",end="")
                        while(1):
                                inp=input()
                                if len(inp)==1:
                                        l[p]=ord(inp)
                                        break
                                else:
                                        print("give value in range 0-9")
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
        print(space)
        print(11*" ",end='')
        for j in l:
                print('|','%3d'%j,'|',sep='',end=' ')
        print()
        print(space)
        print(((p)*6+14)*' ','^',sep='')
        print(((p)*6+14)*' ','|',sep='')
