/************************************************************
ALGraph: ͼ�Ľṹ ͼ�Ĳ���
�洢Ϊ�ڽӱ������һ���ߵļ���arcs
Date: 2013/12/29
Author: searchop
************************************************************/

#ifndef ALGRAPH_H
#define ALGRAPH_H

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;


//�ڽӱ�Ľṹ
struct ArcNode          //����
{
	int source;        //ͼ�иû���Դ�ڵ�
	int adjvex;        //�û���ָ��Ķ����λ��
	ArcNode *nextarc;  //ָ����һ������ָ��
	int weight;         //ÿ���ߵ�Ȩ��
};

struct VertexNode           //ͷ���
{
	char data;    //������Ϣ
	ArcNode *firstarc;  //ָ���һ�������ڸö���Ļ���ָ��
	int key;            //Prim:�������Ӹö�������н������б�����С�ߵ�Ȩ��; 
	//BellmanFord:��¼��Դ��㵽�ý������·��Ȩ�ص��Ͻ�
	VertexNode *p;      //ָ�������еĸ��ڵ�
	int indegree;       //��¼ÿ����������
};

bool operator< (const VertexNode& vn1, const VertexNode &vn2)
{
	return vn1.key < vn2.key;
}

bool operator> (const VertexNode& vn1, const VertexNode &vn2)
{
	return vn1.key > vn2.key;
}

bool operator== (const VertexNode& vn1, const VertexNode &vn2)
{
	return vn1.data == vn2.data && vn1.firstarc == vn2.firstarc
		&& vn1.key == vn2.key && vn1.p == vn2.p;
}

typedef VertexNode VNode;
//������ĸ����Ķ��У���Ҫ����ԭ�������һ����£����ܱ�֤��ȷ��ȡ��topֵ
struct QVNode
{
	VNode node;
	int index;
	QVNode(VNode nd, int i) : node(nd), index(i) {}
	QVNode () {}
};

bool operator< (const QVNode& qvn1, const QVNode &qvn2)
{
       return qvn1.node.key < qvn2.node.key;
}

bool operator> (const QVNode& qvn1, const QVNode &qvn2)
{
	return qvn1.node.key > qvn2.node.key;
}

//QVnode����׼��
class QVNodeCompare
{
public:
	bool operator() (QVNode pvnode1, QVNode pvnode2)
	{
		return pvnode1.node.key > pvnode2.node.key;
	}
};

//ͼ�Ĳ���
class ALGraph
{
public:
	typedef VertexNode VNode;
	ALGraph(int verNum) : vexnum(verNum), arcnum(0)
	{
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			vertices[i].firstarc = NULL;
			vertices[i].key = 1000 ;
			vertices[i].p = NULL;
			vertices[i].indegree = 0;
		}
	}

	//����ͼ������ѡ��
	void Create()
	{
		InitVertics();
	}

	//�����㷨����367ҳͼ����Ȩ����ͼ
	void CreateWUDG()
	{
		cout << "�����㷨����367ҳͼ����Ȩ����ͼ: " << endl;
		for (int i = 0; i < vexnum; i++)
		{
			vertices[i].data = 'a'+i;
		}

		insertArc(0, 1, 4);
		insertArc(0, 7, 8);
		insertArc(1, 2, 8);
		insertArc(1, 7, 11);
		insertArc(2, 3, 7);
		insertArc(2, 8, 2);
		insertArc(2, 5, 4);
		insertArc(3, 4, 9);
		insertArc(3, 5, 14);
		insertArc(4, 5, 10);
		insertArc(5, 6, 2);
		insertArc(6, 7, 1);
		insertArc(6, 8, 6);
		insertArc(7, 8, 7);

		insertArc(1, 0, 4);
		insertArc(7, 0, 8);
		insertArc(2, 1, 8);
		insertArc(7, 1, 11);
		insertArc(3, 2, 7);
		insertArc(8, 2, 2);
		insertArc(5, 2, 4);
		insertArc(4, 3, 9);
		insertArc(5, 3, 14);
		insertArc(5, 4, 10);
		insertArc(6, 5, 2);
		insertArc(7, 6, 1);
		insertArc(8, 6, 6);
		insertArc(8, 7, 7);
	}

	//�����㷨����379ҳͼ����Ȩ����ͼ��
	void createWDG()
	{
		cout << "�����㷨����379ҳͼ����Ȩ����ͼ����" << endl;
		int i;
		for (i = 0; i < 2; i++)
			vertices[i].data = 's' + i;
		for (i = 2; i < vexnum; i++)
			vertices[i].data = 'x'+i-2;

		insertArc(0, 1, 6);
		insertArc(0, 3, 7);
		insertArc(1, 2, 5);
		insertArc(1, 3, 8);
		insertArc(1, 4, -4);
		insertArc(2, 1, -2);
		insertArc(3, 2, -3);
		insertArc(3, 4, 9);
		insertArc(4, 2, 7);
		insertArc(4, 0, 2);
	}

	//�����㷨����382ҳͼ����Ȩ����ͼ��
	void createWDG1()
	{
		cout << "�����㷨����382ҳͼ����Ȩ����ͼ����" << endl;
		int i;
		for (i = 0; i < 3; i++)
			vertices[i].data = 'r' + i;
		for (i = 3; i < vexnum; i++)
			vertices[i].data = 'x'+i-3;

		insertArc(0, 1, 5);
		insertArc(0, 2, 3);
		insertArc(1, 2, 2);
		insertArc(1, 3, 6);
		insertArc(2, 3, 7);
		insertArc(2, 4, 4);
		insertArc(2, 5, 2);
		insertArc(3, 4, -1);
		insertArc(3, 5, 1);
		insertArc(4, 5, -2);
	}

	//�����㷨����384ҳͼ����Ȩ����ͼ��
	void createWDG2()
	{
		cout << "�����㷨����384ҳͼ����Ȩ����ͼ����" << endl;
		int i;
		for (i = 0; i < 2; i++)
			vertices[i].data = 's' + i;
		for (i = 2; i < vexnum; i++)
			vertices[i].data = 'x'+i-2;

		insertArc(0, 1, 10);
		insertArc(0, 3, 5);
		insertArc(1, 2, 1);
		insertArc(1, 3, 2);
		insertArc(2, 4, 4);
		insertArc(3, 1, 3);
		insertArc(3, 2, 9);
		insertArc(3, 4, 2);
		insertArc(4, 2, 6);
		insertArc(4, 0, 7);
	}

	//���ؽ��
	VNode* getVertexNode(int i)
	{
		return &vertices[i-1];
	}

	//��ӡ�ڽ�����
	void displayGraph()
	{
		for (int i = 0; i < vexnum; i++)
		{
			cout << "��" << i+1 << "�������ǣ�" << vertices[i].data
				<< " ��������Ϊ��" << vertices[i].indegree << " �ڽӱ�Ϊ: ";
			ArcNode *arcNode = vertices[i].firstarc;
			while (arcNode != NULL)
			{
				cout << " -> " << vertices[arcNode->adjvex].data
					<< "(" << arcNode->weight << ")";
				arcNode = arcNode->nextarc;
			}
			cout << endl;
		}
		cout << "*******************************************************" << endl;
	}

	struct Arc
	{
		VNode *source;
		VNode *dest;
		int weight;
	};

	//PVnode����׼��
	class PVNodeCompare
	{
	public:
		bool operator() (VNode *pvnode1, VNode *pvnode2)
		{
			return (*pvnode1).key > (*pvnode2).key;
		}
	};

	//Prim�㷨������С������
	void PRIM(int i)
	{
		vertices[i-1].key = 0;    //��ѡ������key��Ϊ0���Ա�ѡ����һ�����ӵ�Ԫ��

		//greater��������С���ѣ�less��Ĭ��Ϊ�󶥶�
		vector<QVNode> qvnode;   //Ӧ�ý�����keyΪ����С����
		for (int i = 0; i < vexnum; i++)
		{
			qvnode.push_back(QVNode(vertices[i], i)); //������ָ�����ν��ӣ����γ�һ��С����
		}
		make_heap(qvnode.begin(), qvnode.end(), greater<QVNode>());
		vector<VNode> vv;     //�������γ��ӵĽ��
		vector<Arc> arcs;  //������С�������ı�

		cout << "Prim�������С��������" << endl;
		while (qvnode.empty() == false)
		{
			VNode node = qvnode[0].node;     //ѡ��һ��������key��С�Ľ��
			vv.push_back(node);         //�����ӵĽ��Ž����飬��Ϊû�а취ֱ����pq���ж�ĳһԪ���Ƿ����ڶ��У�
			//���Ե�һ��Ԫ�ز���vv�У�����pq��....
			Arc arcc;                   
			arcc.source = node.p;  
			arcc.dest = &node;
			arcc.weight = node.key;
			arcs.push_back(arcc);       //��node����ʱ����(node��node->p)�߼ӽ���С��������      

			ArcNode *arc = node.firstarc;    //��ʼ����node���ڽӵ�
			while (arc != NULL)
			{
				//��node�����ٽ���v����Qzhong������v.key���ڱߵ�Ȩ��ʱ��
				//����v��key,���ҽ�v�ĸ������Ϊnode;�������̽�ÿ������key��p�������ˡ�
				if (find(vv.begin(), vv.end(), vertices[arc->adjvex]) == vv.end()
					&& arc->weight < vertices[arc->adjvex].key)
				{
					vertices[arc->adjvex].p = &node;
					vertices[arc->adjvex].key = arc->weight;

					//����qvnode���е��е����ݣ�ʹ��ͽ������ĸı䱣��һ��
					for (int i = 0; i < qvnode.size()-vv.size(); i++)
					{
						if (qvnode[i].index == arc->adjvex)
						{
							qvnode[i].node.p = &node;
							qvnode[i].node.key = arc->weight;
							break;
						}
					}
				}
				arc = arc->nextarc;
			}
			pop_heap(qvnode.begin(), qvnode.end(), greater<QVNode>());
			qvnode.pop_back();
		}
		//��ӡ��С�������ı�
		for (int i = 1; i < arcs.size(); i++)
		{
			cout << "�� " << i << "����Դ���Ϊ��" << (arcs[i].source)->data
				<< " Ŀ�Ľ��Ϊ��" << (arcs[i].dest)->data
				<< " �ߵ�Ȩ��Ϊ��" << arcs[i].weight << endl;
		}
		cout << "*******************************************************" << endl;
	}

	////Prim�㷨������С������
	//void PRIM2(int i)
	//{
	//	vertices[i-1].key = 0;    //��ѡ������key��Ϊ0���Ա�ѡ����һ�����ӵ�Ԫ��
	//	make_heap(vertices, vertices+vexnum);
	//	
	//	vector<VNode> vv;     //�������γ��ӵĽ��
	//	vector<Arc> arcs;  //������С�������ı�

	//	cout << "Prim�������С��������" << endl;
	//	while (vexnum != 0)
	//	{
	//		VNode node = vertices[0];     //ѡ��һ��������key��С�Ľ��
	//		vv.push_back(node);         //�����ӵĽ��Ž����飬��Ϊû�а취ֱ����pq���ж�ĳһԪ���Ƿ����ڶ��У�
	//		//���Ե�һ��Ԫ�ز���vv�У�����pq��....
	//		Arc arcc;                   
	//		arcc.source = node.p;  
	//		arcc.dest = &node;
	//		arcc.weight = node.key;
	//		arcs.push_back(arcc);       //��node����ʱ����(node��node->p)�߼ӽ���С��������      

	//		ArcNode *arc = node.firstarc;    //��ʼ����node���ڽӵ�
	//		while (arc != NULL)
	//		{
	//			//��node�����ٽ���v����Qzhong������v.key���ڱߵ�Ȩ��ʱ��
	//			//����v��key,���ҽ�v�ĸ������Ϊnode;�������̽�ÿ������key��p�������ˡ�
	//			if (find(vv.begin(), vv.end(), vertices[arc->adjvex]) == vv.end()
	//				&& arc->weight < vertices[arc->adjvex].key)
	//			{
	//				vertices[arc->adjvex].p = &node;
	//				vertices[arc->adjvex].key = arc->weight;
	//			}
	//			arc = arc->nextarc;
	//		}
	//		pop_heap(vertices, vertices+vexnum);
	//		vexnum--;			
	//	}
	//	//��ӡ��С�������ı�
	//	for (int i = 1; i < arcs.size(); i++)
	//	{
	//		cout << "�� " << i << "����Դ���Ϊ��" << (arcs[i].source)->data
	//			<< " Ŀ�Ľ��Ϊ��" << (arcs[i].dest)->data
	//			<< " �ߵ�Ȩ��Ϊ��" << arcs[i].weight << endl;
	//	}
	//	cout << "*******************************************************" << endl;
	//}

	//��ÿ���������·�����ƺ�ǰ�������г�ʼ�������·����ʼ��ΪINT_MAX, p��ʼ��ΪNULL
	//����Դ�ڵ��key��ʼ��Ϊ0
	void InitalizeSingleSource(int index)
	{
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			vertices[i].key = INT_MAX>>2;
			vertices[i].p = NULL;
		}
		vertices[index].key = 0;
	}

	//�Աߣ�u, v�������ɳڣ���Ŀǰs��v�����·��v.key��s��u�����·������w(u, v)��ֵ���бȽ�
	//����Ⱥ����ֵ��������и��£���v.key���̣����ҽ�p��Ϊu
	void relax(ArcNode *arc)
	{
		//��Ȼ����ˣ���
		if (vertices[arc->adjvex].key > vertices[arc->source].key + arc->weight)
		{
			vertices[arc->adjvex].key = vertices[arc->source].key + arc->weight;
			vertices[arc->adjvex].p = &vertices[arc->source];
		}
	}

	//BellmanFord
	bool BellmanFord(int index)
	{
		InitalizeSingleSource(index-1);
		for (int i = 1; i < vexnum; i++)     //ѭ��������vexnum-1��
		{
			//�������еıߣ�����ÿ���߽���һ���ɳ�
			for (int j = 0; j < vexnum; j++)
			{
				for (ArcNode *arc = vertices[j].firstarc; arc != NULL; arc = arc->nextarc)
					relax(arc);
			}
		}
		//�ٴα������еıߣ����ͼ���Ƿ����Ȩ��Ϊ��ֵ�Ļ�·��������ڣ��򷵻�false
		for (int j = 0; j < vexnum; j++)
		{
			for (ArcNode *arc = vertices[0].firstarc; arc != NULL; arc = arc->nextarc)
			{
				if (vertices[arc->adjvex].key > vertices[arc->source].key + arc->weight)
					return false;
			}
		}
		cout << "BellmanFord����ĵ�Դ���·����" << endl;
		for (int i = 1; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
		return true;
	}

	//��һ��ջ��¼���Ϊ0�Ľ�㣬��ջ��Ϊ��ʱ��һ������ջ��Ȼ�����α���������
	//���ڽӱ���ÿ���ڽӵĽ�����ȼ�һ���ڽӵĽ����ȱ�Ϊ0ʱ��ջ��ѭ��ֱ��ջΪ��
	//��count��¼��ջ�Ľ�㣬�������vexnum����ͼ�޻�������������ȷ������ͼ�л�
	pair<bool, vector<int> > TopologicalSort()
	{
		stack<VNode> stk;
		vector<int> ivec;
		for (int i = 0; i < vexnum; i++)
		{
			if (vertices[i].indegree == 0)
				stk.push(vertices[i]);
		}

		cout << "ͼ�����������ǣ�" << endl;
		int count = 0;
		while (stk.empty() == false)
		{
			cout << stk.top().data << "->";
			ArcNode *arc = stk.top().firstarc;
			if (arc != NULL)
				ivec.push_back(arc->source);
			stk.pop();			
			count++;
			for (; arc != NULL; arc = arc->nextarc)
			{
				if (!--(vertices[arc->adjvex].indegree))
					stk.push(vertices[arc->adjvex]);
			}
		}
		cout << endl;
		if (count < vexnum)
			return make_pair(false, ivec);
		else
			return make_pair(true, ivec);
	}

	//�������޻�ͼ�У����԰��ս�������˳������ͼ�ı߽����ɳڲ��������Դ��и���Ȩֵ
	//�����������������㣬���Ա�֤��ȫ��������һ�飬��Ϊ��������޻�ͼ���д�u��v��һ��·����
	//��u�����������еĴ���λ�ڽ��v��ǰ�棬
	void DagShortestPaths(int index)
	{
		vector<int> vv = TopologicalSort().second;
		InitalizeSingleSource(index-1);
		for (int i = 0; i < vv.size(); i++)
		{
			ArcNode* arc = vertices[vv[i]].firstarc;
			for (; arc != NULL; arc = arc->nextarc)
				relax(arc);
		}
		cout << "DagShortestPaths����ĵ�Դ���·����" << endl;
		for (int i = index; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
	}

	void Dijkstra(int index)
	{
		InitalizeSingleSource(index-1);
		vector<VNode> snode;
		priority_queue<VNode*, vector<VNode *>, greater<VNode*> > que;

		//�����ָ������У��γ���keyΪ�ؼ�ֵ����С��
		for (int i = 0; i < vexnum; i++)
			que.push(&(vertices[i]));

		while (que.empty() == false)
		{
			VNode *node = que.top();
			snode.push_back(*node);
			for (ArcNode *arc = node->firstarc; arc != NULL; arc = arc->nextarc)
				relax(arc);
			que.pop();
		}
		cout << "Dijkstra����ĵ�Դ���·����" << endl;
		for (int i = index; i < vexnum; i++)
		{
			printPath(index-1, i);
		}
		cout << "**************************************************" << endl;
	}

protected:
	//��ʼ���ڽ�����ı�ͷ����
	void InitVertics()
	{
		cout << "������ÿ������Ĺؼ��֣�" << endl;
		char val;
		for (int i = 0; i < vexnum; i++)
		{
			cin >> val;
			vertices[i].data = val;
		}
	}

	//����һ������
	void insertArc(int vHead, int vTail, int weight)
	{
		//����һ������
		ArcNode *newArcNode = new ArcNode;
		newArcNode->source = vHead;
		newArcNode->adjvex = vTail;
		newArcNode->nextarc = NULL;
		newArcNode->weight = weight;

		//arcNode ��vertics[vHead]���ڽӱ�
		ArcNode *arcNode = vertices[vHead].firstarc;
		if (arcNode == NULL)
			vertices[vHead].firstarc = newArcNode;
		else
		{
			while (arcNode->nextarc != NULL)
			{
				arcNode = arcNode->nextarc;		
			}
			arcNode->nextarc = newArcNode;
		}
		arcnum++;
		vertices[vTail].indegree++;         //�Ի���β������ȼ�1
	}

	//��ӡԴ�ڵ㵽i�����·��
	void printPath(int i, int j)
	{
		cout << "��Դ�ڵ� " << vertices[i].data << " ��Ŀ�Ľ�� "
			<< vertices[j].data << " �����·���ǣ�" /*<< endl*/;
		__printPath(&vertices[i], &vertices[j]);
		cout << " Ȩ��Ϊ��" << vertices[j].key << endl;
	}

	void __printPath(VNode* source, VNode* dest)
	{
		if (source == dest)
			cout << source->data << "->";
		else if (dest->p == NULL)
			cout << " no path��" << endl;
		else
		{
			__printPath(source, dest->p);
			cout << dest->data << "->";
		}
	}

private:
	//const���ݳ�Ա�����ڹ��캯�����ʼ��
	static const int MAX_VERTEX_NUM = 20;  //��󶥵����

	VNode vertices[MAX_VERTEX_NUM];      //��Ž�������

	int vexnum;             //ͼ�ĵ�ǰ������
	int arcnum;             //ͼ�Ļ���
};

#endif