//	�t�@�C����	�Fdefines.hxx
//	  �T  �v		�F�}�N����`
//	��	��	��	�Fdaigo
//	 �쐬����	�F2025/02/21 00:24:03
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef _____DEFINES_HXX_____
#define _____DEFINES_HXX_____

// ���s���[�h
//#define __ENGINE__
#ifndef __ENGINE__
#define BULLET_INPORT_CHECK
#endif // !__ENGINE__


// �r���h���[�h
#ifdef _DEBUG
#define DEBUG
#else
//#define SHIPPING		// 
#endif // !_DEBUG


// �`��API�I��
#define DIRECTX11_PRJ
//#define DIRECTX12_PRJ


// �ǉ�����
#define _THREADPOOL_

#endif // !_____DEFINES_HXX_____