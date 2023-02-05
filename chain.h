#pragma once

template<class child>
class Link{
protected:
	static Link<child>* m_entry;
	Link<child>* m_next;
public:
	Link<child>(){
		m_next = (Link*)0;
	}

	void Chain(){
		Link<child>** indirect = &m_entry;

		while( (*indirect) != ((Link<child>*)0) ){
			if(this == (*indirect))	{
				/* if self is already chained,abort */
				return;
			}

			indirect = &((*indirect)->m_next);
		}

		*indirect = this;
	}

	virtual void Resolve(){};

	static void ResolveChain(){
		Link<child>** focus = &m_entry;
		Link<child>** remove = (Link<child>**)0;

		while( (*focus) != ((Link<child>*)0)){
			(*focus)->Resolve();
			remove = focus;
			focus = &((*focus)->m_next);
			*remove = (Link<child>*)0;
		}
	}
};

template<class child>
Link<child>* Link<child>::m_entry = (Link<child>*)0;
