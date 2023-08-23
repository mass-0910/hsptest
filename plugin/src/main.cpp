#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "hsp3plugin.h"
//#include "hsp3debug.h"
//#include "hsp3struct.h"
//#include "hspwnd.h"

void DrawLine( BMSCR *bm, int x1, int y1, int x2, int y2, int color );

 /*------------------------------------------------------------*/
/*
		controller
*/
/*------------------------------------------------------------*/

static void newcmd2( void )
{
	//		newcmd2 ���߂̏���
	//
	//		(newcmd2 p1,p2)
	//		p1�Ŏw�肵���ϐ���0�`(p2-1)�܂ł̗�������
	//		HSP 2.61�܂ł�rnd���߂Ɠ�������
	//
	PVal *pval;
	APTR aptr;
	aptr = code_getva( &pval );						// �ϐ��̎擾(PVal��APTR�|�C���^)
	p1=code_getdi(100);								// �����l���擾(�f�t�H���g100)
	if (p1==0) puterror( HSPERR_DIVIDED_BY_ZERO );	// 0�Ȃ�΃G���[
	p2 = rand()%p1;									// �����𔭐�������
	code_setva( pval, aptr, HSPVAR_FLAG_INT, &p2 );		// �ϐ��ɒl����(�����l)
}


static void newcmd3( void )
{
	//		newcmd3 ���߂̏���
	//
	//		(newcmd3 "�t�@�C����",p1)
	//		"�t�@�C����"�Ŏw�肵���t�@�C����p1�̓��e�������o��
	//		p1�Ɏw�肳���^�́A�����A�����A������̂����ꂩ�ō\��Ȃ�
	//
	char *p;
	char pathname[_MAX_PATH];
	char out[64];
	int chk;

	p = code_gets();								// ��������擾
	strncpy( pathname, p, _MAX_PATH-1 );			// �擾������������R�s�[

	chk = code_getprm();							// �p�����[�^�[���擾(�^�͖��Ȃ�)
	if ( chk<=PARAM_END ) {
		return;										// �p�����[�^�[�ȗ����̏���
	}

	int type = mpval->flag;							// �p�����[�^�[�̌^���擾
	switch( type ) {
	case HSPVAR_FLAG_STR:								// �p�����[�^�[�������񂾂�����
		{
		char *str = (char *)mpval->pt;
		sprintf( out,"%s\n%s\n", pathname, str );
		break;
		}
	case HSPVAR_FLAG_DOUBLE:									// �p�����[�^�[��������������
		{
		double *ptr = (double *)mpval->pt;
		sprintf( out,"%s\n%f\n", pathname, *ptr );
		break;
		}
	case HSPVAR_FLAG_INT:									// �p�����[�^�[��������������
		{
		int *ptr = (int *)mpval->pt;
		sprintf( out,"%s\n%d\n", pathname, *ptr );
		break;
		}
	default:
		puterror( HSPERR_TYPE_MISMATCH );			// �T�|�[�g���Ă��Ȃ��^�Ȃ�΃G���[
	}

	//	������out���t�@�C���ɒǋL�ŏ����o��
	//
	FILE *fp;
	fp = fopen( pathname, "a" );
	fputs( out, fp );
	fclose( fp );
}


static void newcmd4( void )
{
	//		newcmd4 ���߂̏���
	//
	//		(newcmd4 x1,y1,x2,y2,color)
	//		(x1,y1)����(x2,y2)�܂�color�Ŏw�肵���F�̐�������
	//
	BMSCR *bm;

	p1 = code_getdi(0);		// �p�����[�^1:���l
	p2 = code_getdi(0);		// �p�����[�^2:���l
	p3 = code_getdi(0);		// �p�����[�^3:���l
	p4 = code_getdi(0);		// �p�����[�^4:���l
	p5 = code_getdi(0);		// �p�����[�^5:���l

	bm = (BMSCR *)getbmscr( active_window );	// ���݂�BMSCR���擾
	DrawLine( bm, p1, p2, p3, p4, p5 );
	bms_send( bm, 0, 0, bm->sx, bm->sy );		// �S��ʂ��X�V
}

/*------------------------------------------------------------*/

static int cmdfunc( int cmd )
{
	//		���s���� (���ߎ��s���ɌĂ΂�܂�)
	//
	code_next();							// ���̃R�[�h���擾(�ŏ��ɕK���K�v�ł�)

	switch( cmd ) {							// �T�u�R�}���h���Ƃ̕���

	case 0x00:								// newcmd

		p1 = code_getdi( 123 );		// �����l���擾(�f�t�H���g123)
		stat = p1;					// �V�X�e���ϐ�stat�ɑ��
		break;

	case 0x01:								// newcmd2
		newcmd2();
		break;

	case 0x02:								// newcmd3
		newcmd3();
		break;

	case 0x03:								// newcmd4
		newcmd4();
		break;

	default:
		puterror( HSPERR_UNSUPPORTED_FUNCTION );
	}
	return RUNMODE_RUN;
}


/*------------------------------------------------------------*/

static int ref_ival;						// �Ԓl�̂��߂̕ϐ�

static void *reffunc( int *type_res, int cmd )
{
	//		�֐��E�V�X�e���ϐ��̎��s���� (�l�̎Q�Ǝ��ɌĂ΂�܂�)
	//
	//			'('�Ŏn�܂邩�𒲂ׂ�
	//
	if ( *type != TYPE_MARK ) puterror( HSPERR_INVALID_FUNCPARAM );
	if ( *val != '(' ) puterror( HSPERR_INVALID_FUNCPARAM );
	code_next();


	switch( cmd ) {							// �T�u�R�}���h���Ƃ̕���

	case 0x00:								// newcmd

		p1 = code_geti();				// �����l���擾(�f�t�H���g�Ȃ�)
		ref_ival = p1 * 2;				// �Ԓl��ival�ɐݒ�
		break;

	default:
		puterror( HSPERR_UNSUPPORTED_FUNCTION );
	}

	//			'('�ŏI��邩�𒲂ׂ�
	//
	if ( *type != TYPE_MARK ) puterror( HSPERR_INVALID_FUNCPARAM );
	if ( *val != ')' ) puterror( HSPERR_INVALID_FUNCPARAM );
	code_next();

	*type_res = HSPVAR_FLAG_INT;			// �Ԓl�̃^�C�v�𐮐��Ɏw�肷��
	return (void *)&ref_ival;
}


/*------------------------------------------------------------*/

static int termfunc( int option )
{
	//		�I������ (�A�v���P�[�V�����I�����ɌĂ΂�܂�)
	//
	return 0;
}

/*------------------------------------------------------------*/

int eventfunc( int event, int prm1, int prm2, void *prm3 )
{
	//		�C�x���g���� (HSP�C�x���g�������ɌĂ΂�܂�)
	//
    MessageBox(NULL, static_cast<LPCSTR>(std::to_string(event).c_str()), TEXT("HOGE"), MB_OK);
	switch( event ) {
    case HSPEVENT_COMMAND:
        break;
	case HSPEVENT_GETKEY:
		{
		int *ival;
		ival = (int *)prm3;
		*ival = 125;
		return 1;
		}
	}
	return 0;
}

/*------------------------------------------------------------*/
/*
		interface
*/
/*------------------------------------------------------------*/

int WINAPI DllMain (HINSTANCE hInstance, DWORD fdwReason, PVOID pvReserved)
{
	//		DLL�G���g���[ (��������K�v�͂���܂���)
	//
	return TRUE;
}


EXPORT void WINAPI hsp3cmdinit( HSP3TYPEINFO *info )
{
	//		�v���O�C�������� (���s�E�I��������o�^���܂�)
	//
	hsp3sdk_init( info );			// SDK�̏�����(�ŏ��ɍs�Ȃ��ĉ�����)
	info->cmdfunc = cmdfunc;		// ���s�֐�(cmdfunc)�̓o�^
	info->reffunc = reffunc;		// �Q�Ɗ֐�(reffunc)�̓o�^
	info->termfunc = termfunc;		// �I���֐�(termfunc)�̓o�^

	//	�C�x���g�R�[���o�b�N�𔭐�������C�x���g��ʂ�ݒ肷��
    info->option = HSPEVENT_ENABLE_COMMAND | HSPEVENT_ENABLE_HSPIRQ | HSPEVENT_ENABLE_GETKEY;
	info->eventfunc = eventfunc;	// �C�x���g�֐�(eventfunc)�̓o�^
}

/*------------------------------------------------------------*/

/*
EXPORT BOOL WINAPI test1( PVAL2 *pval, int p1, int p2, int p3 )
{
	//	DLL test1 (type$83)
	//		�w�肵���ϐ��ɁA�u������e�X�g�v��������B
	//		�ϐ��̌^�����l�^�������ꍇ���A������^�ɂ���B
	//
	char *pt;
	if (pval->flag==4) pval->flag=2;	// ������^��
	pt=pval->pt;
	strcpy( pt,"������e�X�g" );
	return 0;
}


EXPORT BOOL WINAPI test2( HSPEXINFO *hei, int p1, int p2, int p3 )
{
	//	DLL test2 (type$202)
	//		test2 �ϐ�,"�t�@�C����"
	//		�w�肵���e�L�X�g�t�@�C����ϐ��o�b�t�@�ɓǂݍ��ށB
	//		�t�@�C���T�C�Y�ɍ��킹�ĕϐ��o�b�t�@���g������B
	//		packfile�Ŏw�肵���t�@�C�����ǂݍ��݉\�B
	//
	int cursize, newsize;
	PVAL2 *pval;
	char *ep1;
	char *ep2;
	ep1 = (char *)hei->HspFunc_prm_getv();	// �p�����[�^1:�ϐ�
	pval = *hei->pval;						// �ϐ���PVAL2�|�C���^���擾
	ep2 = hei->HspFunc_prm_gets();			// �p�����[�^2:������
	if ( *hei->er ) return *hei->er;		// �G���[�`�F�b�N
	cursize = valsize( pval );				// �ϐ��̃������T�C�Y���擾
	newsize = hei->HspFunc_fsize( ep2 );	// �t�@�C���̃T�C�Y���擾
	if ( newsize<0 ) return -1;				// �t�@�C�����Ȃ��ꍇ�͏I��
	if ( newsize>cursize ) {
		//	�t�@�C���ǂݍ��݂ɕK�v�ȃo�b�t�@���m��
		hei->HspFunc_val_realloc( pval,newsize,0 );
	}
	hei->HspFunc_fread( ep2, pval->pt, newsize, 0 );	// �t�@�C���ǂݍ���
	return 0;
}


EXPORT BOOL WINAPI test3( BMSCR *bm, int p1, int p2, char *p3 )
{
	//	DLL test3 (type$32)
	//		test3 p1,p2
	//		�p���b�g��p1�`p2�܂łɃO���[�X�P�[���̃O���f�[�V������
	//		�ݒ肷��B
	//
	int a,n,len,grade;
	int x1,x2,px;
	char *pt;
	len=p2-p1;
	x1=p1<<8;x2=p2<<8;px=(255<<8)/len;
	for(a=0;a<len;a++) {
		n=a+p1;								// n=�p���b�g�ԍ�
		pt=p3+(n*3);						// �p���b�g�A�h���X�v�Z
		grade=x1>>8;
		pt[0]=grade;						// R�̋P�x
		pt[1]=grade;						// G�̋P�x
		pt[2]=grade;						// B�̋P�x
		x1+=px;
	}
	bms_setpal( bm, bm->pals, p3 );
	bms_update( bm );
	return 0;
}


EXPORT BOOL WINAPI test4( HSPEXINFO *hei, int p1, int p2, int p3 )
{
	//	DLL test4 (type$202)
	//		test4 �ϐ�,���l1,���l2,���l3,���l4,���l5,���l6
	//		�����̃p�����[�^�[���󂯎��e�X�g�B
	//		���l1�`6�܂ł̍��v��ϐ�a�ɑ���B
	//
	int ep2,ep3,ep4,ep5,ep6,ep7;
	int *ep1;
	ep1 = (int *)hei->HspFunc_prm_getv();	// �p�����[�^1:�ϐ�
	ep2 = hei->HspFunc_prm_getdi(0);		// �p�����[�^2:���l
	ep3 = hei->HspFunc_prm_getdi(0);		// �p�����[�^3:���l
	ep4 = hei->HspFunc_prm_getdi(0);		// �p�����[�^4:���l
	ep5 = hei->HspFunc_prm_getdi(0);		// �p�����[�^5:���l
	ep6 = hei->HspFunc_prm_getdi(0);		// �p�����[�^6:���l
	ep7 = hei->HspFunc_prm_getdi(0);		// �p�����[�^7:���l
	if ( *hei->er ) return *hei->er;		// �G���[�`�F�b�N
	*ep1 = ep2+ep3+ep4+ep5+ep6+ep7;
	return 0;
}


EXPORT BOOL WINAPI test5( HSPEXINFO *hei, int p1, int p2, int p3 )
{
	//	DLL test5 (type$202)
	//		test5 X1���W,Y1���W,X2���W,Y2���W,RGB�l
	//
	BMSCR *bm;
	int ep1,ep2,ep3,ep4,ep5;
	ep1 = hei->HspFunc_prm_getdi(0);		// �p�����[�^1:���l
	ep2 = hei->HspFunc_prm_getdi(0);		// �p�����[�^2:���l
	ep3 = hei->HspFunc_prm_getdi(0);		// �p�����[�^3:���l
	ep4 = hei->HspFunc_prm_getdi(0);		// �p�����[�^4:���l
	ep5 = hei->HspFunc_prm_getdi(0);		// �p�����[�^5:���l
	if ( *hei->er ) return *hei->er;		// �G���[�`�F�b�N
	bm = (BMSCR *)hei->HspFunc_getbmscr( *hei->actscr );	// ���݂�BMSCR���擾
	DrawLine( bm, ep1, ep2, ep3, ep4, ep5 );
	return 0;
}


EXPORT BOOL WINAPI test6( HSPEXINFO *hei, int p1, int p2, int p3 )
{
	//	DLL test6 (type$202)
	//		test6 prm
	//
	int type,val;
	int *strsize;
	char *es1;
	char *refstr;
	int ep1;
	strsize = hei->strsize;
	refstr = hei->refstr;
	type = *hei->nptype;
	val = *hei->npval;
	switch( type ) {
	case 1:
		ep1 = hei->HspFunc_prm_getdi(0);		// �p�����[�^1:���l
		*strsize = ep1;
		break;
	case 2:
		es1 = hei->HspFunc_prm_gets();			// �p�����[�^1:������
		strcpy( refstr, es1 );
		break;
	case 4:
		ep1 = hei->HspFunc_prm_getv();			// �p�����[�^1:�ϐ�
		*strsize = ep1;
		break;
	default:
		return 2;
	}
	return -type;
}
*/

/*------------------------------------------------------------*/
/*
		(���܂�) Line Draw Routines (�t���J���[�p)
*/
/*------------------------------------------------------------*/

void DrawLine( BMSCR *bm, int x1, int y1, int x2, int y2, int color )
{
	char *lpDest;		// �`���ʂ̃o�b�t�@
	int nDestWByte;		// �`����W��byte��
	int nDestWidth;		// �`����W��
	int nDestHeight;	// �`����W����
	int DestSize;		// �`���ʃo�b�t�@�̃T�C�Y
    int i, x, y, dx, dy, addx, addy;
	short color1;
	unsigned char color2;
	unsigned char *up;
	char *dwDest;
    int cnt = 0;

	lpDest = (char *)bm->pBit;
	nDestWidth = bm->sx;
	nDestWByte = bm->sx*3;
	nDestHeight = bm->sy;
	DestSize = bm->sx*bm->sy*3;

	dwDest = lpDest + ((nDestHeight-1)*nDestWByte);
	color1 = (short)(color & 0xffff);
	color2 = (unsigned char)( (color & 0xff0000 ) >>16 );

    dx = x2 - x1;
    if (dx < 0){ addx = -1; dx = -dx; } else addx = 1;
    dy = y2 - y1;
    if (dy < 0){ addy = -1; dy = -dy; } else addy = 1;
    x = x1; y = y1;

    if (dx > dy){
        for (i = 0; i < dx; ++i){
			if ((y>=0)&&(y<nDestHeight)&&(x>=0)&&(x<nDestWidth)) {
				up = (unsigned char *)(dwDest - nDestWByte*y + x*3 );
				*(short *)up = color1; up[2] = color2;
			}
            cnt += dy; x += addx;
            if (cnt >= dx){ cnt-=dx; y+=addy; }
        }
    }
    else{
        for (i = 0; i < dy; ++i){
			if ((y>=0)&&(y<nDestHeight)&&(x>=0)&&(x<nDestWidth)) {
				up = (unsigned char *)(dwDest - nDestWByte*y + x*3 );
				*(short *)up = color1; up[2] = color2;
			}
            cnt += dx; y += addy;
            if (cnt >= dy){ cnt-=dy; x+=addx; }
        }
    }
	return;
}


/*----------------------------------------------------------------*/
