#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H

#include "list.h"
#include <ctime>
#include <unordered_map>

struct SearchResult
{
        bool pathfound; //���� ������
        float pathlength; //����� ����, ���� ���� �� ������, �� ����� 0
        /*const*/ NodeList* lppath; //���� � ���� ������������������ ������
        /*const*/ NodeList* hppath; //���� �������� �� ������
        unsigned int nodescreated; //|OPEN| + |CLOSE| = ����� ��������� ����� (= ���������� ��������� ������������� ������)
        unsigned int numberofsteps; //����� �������� (= ���������� ��������� ������������� ������)
        double time; //���������� ����������� ����� (= "����������" (�� ��������� �� ���������� ����������) ���������� ��������� ������������� ������)
        SearchResult()
        {
            pathfound = false;
            pathlength = 0;
            lppath = NULL;
            hppath = NULL;
            nodescreated = 0;
            numberofsteps = 0;
            time = 0;
        }

        /*void push_front_lppath(Node n) {
            lppath = lppath->push_front(n);
        }

        void push_front_hppath(Node n) {
            hppath = hppath->push_front(n);
        }*/

};

#endif
