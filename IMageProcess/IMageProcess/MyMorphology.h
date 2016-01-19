#pragma once
class CMyMorphology
{
public:
	CMyMorphology(void);
	~CMyMorphology(void);
protected:
public:
	void grayDilation(CImage *, int *);
	void grayErosion(CImage *, int *);
	void grayOpening(CImage *, int *);
	void grayClosing(CImage *, int *);
	void grayEdge(CImage *, int *);

	void binaryDilation(CImage *, int *); // 直接使用3*3 kerne
	void binaryErosion(CImage *, int *);
	void binaryOpening(CImage *, int *);
	void binaryClosing(CImage *, int *);
	void binaryDelete(CImage *, int *);
	int * binarykernel();
	int * graykernel();
};

