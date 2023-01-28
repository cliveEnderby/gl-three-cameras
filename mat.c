#include"mat.h"
float q[16],Q[16];
float *vecPoint(float *v,float x, float y, float z)
{	//ok
	v[0]=x;
	v[1]=y;
	v[2]=z;
	v[3]=1.0f;
	return v;
}
float *vecVec(float *v,float x,float y,float z)
{	//ok
	v[0]=x;
	v[1]=y;
	v[2]=z;
	v[3]=0.0f;
	return v;
}
float *vecAdd(float *v,const float *m, const float *n)
{	//ok
	v[0] = m[0]+n[0];
	v[1] = m[1]+n[1];
	v[2] = m[2]+n[2];
	v[3] = m[3]+n[3];
	return v;
}
float *vecDivW(float *v,const float *m)
{
	v[0]=m[0]/m[3];
	v[1]=m[1]/m[3];
	v[2]=m[2]/m[3];
	v[3]=1.0;
	return v;
}
float *vecSub(float *v,const float *m, const float *n)
{	//ok
	v[0] = m[0]-n[0];
	v[1] = m[1]-n[1];
	v[2] = m[2]-n[2];
	v[3] = m[3]-n[3];
	return v;
}
float *vecMult(float *v, const float *m, float d)
{	//ok
	v[0]=m[0]*d;
	v[1]=m[1]*d;
	v[2]=m[2]*d;
	v[3]=m[3]*d;
	return v;
}
float *vecCopy(float *v, const float *m)
{	//ok
	v[0]=m[0];
	v[1]=m[1];
	v[2]=m[2];
	v[3]=m[3];
	return v;
}
float vecMag(const float *v)
{	//ok
	return sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] +v[3]*v[3]);
}
float vecDot(const float *v1, const float *v2)
{	//ok
	return	v1[0]*v2[0]+
			v1[1]*v2[1]+
			v1[2]*v2[2];
}
float *vecCross(float *o,  const float *m1, const float *m2)
{	//hope so
	q[0]=m1[1]*m2[2]-m1[2]*m2[1];
	q[1]=m1[2]*m2[0]-m1[0]*m2[2];
	o[2]=m1[0]*m2[1]-m1[1]*m2[0];
	o[0]=q[0];
	o[1]=q[1];
	o[3] = 0.0f;
	return o;
}
float *vecNorm(float *v1, const float *v2)
{	//ok
	float mag=vecMag(v1);
	v1[0]=v2[0]/mag;
	v1[1]=v2[1]/mag;
	v1[2]=v2[2]/mag;
	v1[3]=v2[3]/mag;
	return v1;
}
bool vecComp(const float *v1, const float *v2)
{
	const float epsilon = 0.00001f;
	if ((v1[0]-v2[0])*(v1[0]-v2[0])>epsilon) return false;
	if ((v1[1]-v2[1])*(v1[1]-v2[1])>epsilon) return false;
	if ((v1[2]-v2[2])*(v1[2]-v2[2])>epsilon) return false;
	if ((v1[3]-v2[3])*(v1[3]-v2[3])>epsilon) return false;
	return true;
}
const float *vecPrint(const float *v)
{
	printf("[% 05.3f % 05.3f % 05.3f % 05.3f]\n",v[0],v[1],v[2],v[3]);
	return v;
}
float *matZero(float *m)
{
	for(int i=0;i<16;i++)
		m[i]=0.0f;
	return m;
}
float *matOne(float *m)
{
	for(int i=0;i<16;i++)
		m[i]=i%5?0:1;
	return m;
}
const float *matPrint(const float *m)
{
	for(int i=0;i<4;i++)
	{
		printf(":");
		for(int j=0;j<4;j++)
		{
			printf(" % 06.3f",m[i+4*j]);
		}
		printf(" :\n");
	}
	return m;
}
float *matCopy(float *o,const float *m)
{
	for(int i=0;i<16;i++)o[i]=m[i];
	return o;
}
float *matTranslate(float *m, float x, float y, float z)
{
	m[ 0] = 1; m[ 4] = 0; m[ 8] = 0; m[12] = x;
	m[ 1] = 0; m[ 5] = 1; m[ 9] = 0; m[13] = y;
	m[ 2] = 0; m[ 6] = 0; m[10] = 1; m[14] = z;
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
	return m;
}
float *matTranslateV(float *m, const float *v)
{
	m[ 0] = 1; m[ 4] = 0; m[ 8] = 0; m[12] = v[0];
	m[ 1] = 0; m[ 5] = 1; m[ 9] = 0; m[13] = v[1];
	m[ 2] = 0; m[ 6] = 0; m[10] = 1; m[14] = v[2];
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = v[3];
	return m;
}
float *matScale(float *m, float x, float y, float z)
{
	m[ 0] = x; m[ 4] = 0; m[ 8] = 0; m[12] = 0;
	m[ 1] = 0; m[ 5] = y; m[ 9] = 0; m[13] = 0;
	m[ 2] = 0; m[ 6] = 0; m[10] = z; m[14] = 0;
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
	return m;
}

float *matPerspective(float *m, float fov, float aspect, float near, float far)
{
	float m5=1.0f/tanf(fov/2.0f);
	float m0=m5/aspect;
	float m10=(near+far)/(near-far);
	float m14=(2*near*far)/(near-far);
	
	m[ 0] = m0; m[ 4] = 0;  m[ 8] = 0;   m[12] = 0;
	m[ 1] = 0;  m[ 5] = m5; m[ 9] = 0;   m[13] = 0;
	m[ 2] = 0;  m[ 6] = 0;  m[10] = m10; m[14] = m14;
	m[ 3] = 0;  m[ 7] = 0;  m[11] =-1;   m[15] = 0;
	return m;
}
float *matRotX(float *m, float a)
{
	float s = sinf(a);
	float c = cosf(a);
	m[ 0] = 1; m[ 4] = 0; m[ 8] = 0; m[12] = 0;
	m[ 1] = 0; m[ 5] = c; m[ 9] =-s; m[13] = 0;
	m[ 2] = 0; m[ 6] = s; m[10] = c; m[14] = 0;
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
	return m;
}   
float *matRotY(float *m, float a)
{
	float s = sinf(a);
	float c = cosf(a);
	m[ 0] = c; m[ 4] = 0; m[ 8] = s; m[12] = 0;
	m[ 1] = 0; m[ 5] = 1; m[ 9] = 0; m[13] = 0;
	m[ 2] =-s; m[ 6] = 0; m[10] = c; m[14] = 0;
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
	return m;
}
float *matRotZ(float *m, float a)
{
	float s = sinf(a);
	float c = cosf(a);
	m[ 0] = c; m[ 4] =-s; m[ 8] = 0; m[12] = 0;
	m[ 1] = s; m[ 5] = c; m[ 9] = 0; m[13] = 0;
	m[ 2] = 0; m[ 6] = 0; m[10] = 1; m[14] = 0;
	m[ 3] = 0; m[ 7] = 0; m[11] = 0; m[15] = 1;
	return m;
}
float *vecQuat(float *v, float x,float y, float z, float w)
{
	float S=sinf(w/2.0f);
	float l=sqrtf(x*x+y*y+z*z);
	v[0]=S*x/l;
	v[1]=S*y/l;
	v[2]=S*z/l;
	v[3]=cosf(w/2.0f);
	return v;
}
float *quatX(float *v,const float *m, const float *n)
{
	q[0] = m[3]*n[0] + m[0]*n[3] + m[1]*n[2] - m[2]*n[1];
	q[1] = m[3]*n[1] - m[0]*n[2] + m[1]*n[3] + m[2]*n[0];
	q[2] = m[3]*n[2] + m[0]*n[1] - m[1]*n[0] + m[2]*n[3];
	v[3] = m[3]*n[3] - m[0]*n[0] - m[1]*n[1] - m[2]*n[2];
	v[0]=q[0];
	v[1]=q[1];
	v[2]=q[2];
	return v;
}
float *matQuat(float *p, const float *v)
{
	q[0]=1-2*v[1]*v[1]-2*v[2]*v[2];
	 q[4]=  2*v[0]*v[1]+2*v[2]*v[3];
	   q[8]=  2*v[0]*v[2]-2*v[1]*v[3];
		q[12] = 0;
	q[1]=2*v[0]*v[1]-2*v[2]*v[3];
	 q[5]=1-2*v[0]*v[0]-2*v[2]*v[2];
	  q[9]=2*v[1]*v[2]+2*v[0]*v[3];
	   q[13] = 0;
	q[2]=2*v[0]*v[2]+2*v[1]*v[3];
	 q[6]=2*v[1]*v[2]-2*v[0]*v[3];
	  q[10]=1-2*v[0]*v[0]-2*v[1]*v[1];
	   q[14] = 0;
	p[0]=q[0];  p[1]=q[1];  p[2]=q[2];  p[3]=0;
	p[4]=q[4];  p[5]=q[5];  p[6]=q[6];  p[7]=0;
	p[8]=q[8];  p[9]=q[9];  p[10]=q[10];p[11]=0;
	p[12]=q[12];p[13]=q[13];p[14]=q[14];p[15]=1.0f;
	return p;
}

float *matOrtho(float *p, 
					float l, float r, float b,
					float t, float n, float f)
{
	float A= 2/(r-l);
	float B= 2/(t-b);
	float C=-2/(f-n);
	float D=(r+l)/(r-l);
	float E=(t+b)/(t-b);
	float F=(f+n)/(f-n);

	p[ 0]=A;p[ 4]=0;p[ 8]=0;p[12]=-D;
	p[ 1]=0;p[ 5]=B;p[ 9]=0;p[13]=-E;
	p[ 2]=0;p[ 6]=0;p[10]=C;p[14]=-F;
	p[ 3]=0;p[ 7]=0;p[11]=0;p[15]=1;
	return p;
}

float *matVec(float *o, const float *m, const float *v)	
{
	q[0]=m[ 0]*v[0] + m[ 4]*v[1] + m[ 8]*v[2] + m[12]*v[3];
	q[1]=m[ 1]*v[0] + m[ 5]*v[1] + m[ 9]*v[2] + m[13]*v[3];
	q[2]=m[ 2]*v[0] + m[ 6]*v[1] + m[10]*v[2] + m[14]*v[3];
	o[3]=m[ 3]*v[0] + m[ 7]*v[1] + m[11]*v[2] + m[15]*v[3];
	o[0]=q[0];o[1]=q[1];o[2]=q[2];
	return o;
}
void matMatSub(const float *m, const float *n)
{
	q[ 0]=m[ 0]*n[ 0] + m[ 4]*n[ 1] + m[ 8]*n[ 2] + m[12]*n[ 3];
	q[ 4]=m[ 0]*n[ 4] + m[ 4]*n[ 5] + m[ 8]*n[ 6] + m[12]*n[ 7];
	q[ 8]=m[ 0]*n[ 8] + m[ 4]*n[ 9] + m[ 8]*n[10] + m[12]*n[11];
	q[12]=m[ 0]*n[12] + m[ 4]*n[13] + m[ 8]*n[14] + m[12]*n[15];

	q[ 1]=m[ 1]*n[ 0] + m[ 5]*n[ 1] + m[ 9]*n[ 2] + m[13]*n[ 3];
	q[ 5]=m[ 1]*n[ 4] + m[ 5]*n[ 5] + m[ 9]*n[ 6] + m[13]*n[ 7];
	q[ 9]=m[ 1]*n[ 8] + m[ 5]*n[ 9] + m[ 9]*n[10] + m[13]*n[11];
	q[13]=m[ 1]*n[12] + m[ 5]*n[13] + m[ 9]*n[14] + m[13]*n[15];
	
	q[ 2]=m[ 2]*n[ 0] + m[ 6]*n[ 1] + m[10]*n[ 2] + m[14]*n[ 3];
	q[ 6]=m[ 2]*n[ 4] + m[ 6]*n[ 5] + m[10]*n[ 6] + m[14]*n[ 7];
	q[10]=m[ 2]*n[ 8] + m[ 6]*n[ 9] + m[10]*n[10] + m[14]*n[11];
	q[14]=m[ 2]*n[12] + m[ 6]*n[13] + m[10]*n[14] + m[14]*n[15];

	q[ 3]=m[ 3]*n[ 0] + m[ 7]*n[ 1] + m[11]*n[ 2] + m[15]*n[ 3];
	q[ 7]=m[ 3]*n[ 4] + m[ 7]*n[ 5] + m[11]*n[ 6] + m[15]*n[ 7];
	q[11]=m[ 3]*n[ 8] + m[ 7]*n[ 9] + m[11]*n[10] + m[15]*n[11];
	q[15]=m[ 3]*n[12] + m[ 7]*n[13] + m[11]*n[14] + m[15]*n[15];
}
float *matMat(float *o,const float *m, const float *n)
{
	matMatSub(m,n);
	o[ 0]=q[ 0];o[ 4]=q[ 4];o[ 8]=q[ 8];o[12]=q[12];
	o[ 1]=q[ 1];o[ 5]=q[ 5];o[ 9]=q[ 9];o[13]=q[13];
	o[ 2]=q[ 2];o[ 6]=q[ 6];o[10]=q[10];o[14]=q[14];
	o[ 3]=q[ 3];o[ 7]=q[ 7];o[11]=q[11];o[15]=q[15];
	return o;
}
float *matMultiMat(float *o,const float **ms)
{
	int i;
	for(i=0;ms[i];i++);
	matCopy(Q,ms[i-1]);
	for(i=i-2;i>=0;i--)
	{
		matMatSub(ms[i],Q);
		matCopy(Q,q);
	}
	matCopy(o,Q);
	return o;
}
float *matTranspose(float *o, const float *m)
{
	q[ 0]=m[ 0];q[ 4]=m[ 1];q[ 8]=m[ 2];q[12]=m[ 3];
	q[ 1]=m[ 4];q[ 5]=m[ 5];q[ 9]=m[ 6];q[13]=m[ 7];
	q[ 2]=m[ 8];q[ 6]=m[ 9];q[10]=m[10];q[14]=m[11];
	q[ 3]=m[12];q[ 7]=m[13];q[11]=m[14];q[15]=m[15];
	
	o[ 0]=q[ 0];o[ 4]=q[ 4];o[ 8]=q[ 8];o[12]=q[12];
	o[ 1]=q[ 1];o[ 5]=q[ 5];o[ 9]=q[ 9];o[13]=q[13];
	o[ 2]=q[ 2];o[ 6]=q[ 6];o[10]=q[10];o[14]=q[14];
	o[ 3]=q[ 3];o[ 7]=q[ 7];o[11]=q[11];o[15]=q[15];
	return o;
}

float matCofactor(int p, const float *m)
{
	int x=p/4;
	int y=p%4;
	float cof=0;
	for(int c=0;c<3;c++)
	{
		int y1 = (y+1)%4;
		int x1 = (x+c+1)%4;
		int aby = (y1+1)%4;
		int acx = (x+1+((c+1)%3))%4;
		int cdy = (y1+2)%4;
		int bdx = (x+1+((c+2)%3))%4;
		
		cof+=m[y1+(x1<<2)]*
			(
					m[aby+(acx<<2)]*m[cdy+(bdx<<2)] -
					m[aby+(bdx<<2)]*m[cdy+(acx<<2)]
			);
	}
	if((p+(p>>2))%2)cof*=-1;
	return cof;
}
float matDet(const float *m)
{
	return 
		m[ 0]*matCofactor( 0,m)+
		m[ 4]*matCofactor( 4,m)+
		m[ 8]*matCofactor( 8,m)+
		m[12]*matCofactor(12,m);
}
float *matInverse(float *o, const float *in)
{
	float d = matDet(in);
	for(int r=0;r<4;r++)
	{
		for(int c=0;c<4;c++)
		{
			q[r+4*c]=matCofactor(r*4+c,in)/d;
		}
	}
	o[ 0]=q[ 0];o[ 4]=q[ 4];o[ 8]=q[ 8];o[12]=q[12];
	o[ 1]=q[ 1];o[ 5]=q[ 5];o[ 9]=q[ 9];o[13]=q[13];
	o[ 2]=q[ 2];o[ 6]=q[ 6];o[10]=q[10];o[14]=q[14];
	o[ 3]=q[ 3];o[ 7]=q[ 7];o[11]=q[11];o[15]=q[15];
	return o;
}

