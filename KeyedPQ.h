//
//  IndexPQ.h
//
//  Implementación de colas con prioridad mediante montículos.
//  Los elementos son enteros de 0 a N-1 que tienen asociada una prioridad
//  dentro de la cola. La prioridad de un elemento puede ser modificada
//  con coste en O(log N).
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef INDEXPQ_H_
#define INDEXPQ_H_

#include <iostream>
#include <stdexcept>
#include <vector>
#include <unordered_map>

// T es el tipo de las prioridades
// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename K = int, typename T = int, typename Comparator = std::less<T>>
class KeyedPQ
{
public:
   // registro para las parejas < elem, prioridad >
   struct Par
   {
      K elem;
      T prioridad;
   };

private:
   // vector que contiene los datos (pares < elem, prio >)
   std::vector<Par> array; // primer elemento en la posición 1

   // vector que contiene las posiciones en array de los elementos
   std::unordered_map<K, int> posiciones; // un 0 indica que el elemento no está

   /* Objeto función que sabe comparar prioridades.
    antes(a,b) es cierto si a es más prioritario que b */
   Comparator antes;

public:
   KeyedPQ(Comparator c = Comparator()) : array(1), posiciones(), antes(c) {}

   KeyedPQ(KeyedPQ<K, T, Comparator> const &) = default;

   KeyedPQ<K, T, Comparator> &operator=(KeyedPQ<K, T, Comparator> const &) = default;

   ~KeyedPQ() = default;

   // e debe ser uno de los posibles elementos
   void push(K e, T const &p)
   {
      if (posiciones.count(e) != 0)
         throw std::invalid_argument("No se pueden insertar elementos repetidos.");
      else
      {
         array.push_back({e, p});
         posiciones[e] = size();
         flotar(size());
      }
   }

   void update(K e, T const &p)
   {
      if (posiciones.count(e) == 0) // el elemento e se inserta por primera vez
         push(e, p);
      else
      {
         int i = posiciones.at(e);
         array[i].prioridad = p;
         if (i != 1 && antes(array[i].prioridad, array[i / 2].prioridad))
            flotar(i);
         else // puede hacer falta hundir a e
            hundir(i);
      }
   }

   void mostrartop3() const
   {
      if (size() >= 3)
      {

         if (array[1].prioridad.m != 0)
            std::cout << 1 << " " << array[1].elem << "\n";
         int second = antes(array[2].prioridad, array[3].prioridad) ? 2 : 3;
         int third = second == 2 ? 3 : 2;
         for (int i = 2 * second; i <= size() && i < 2 * second + 2; i++)
            if (antes(array[i].prioridad, array[third].prioridad) && array[i].prioridad.m != 0)
               third = i;
         if (array[second].prioridad.m != 0)
            std::cout << 2 << " " << array[second].elem << "\n";
         if (array[third].prioridad.m != 0)
            std::cout << 3 << " " << array[third].elem << "\n";
      }
      else
      {
         for (int i = 1; i <= size() && array[i].prioridad.m != 0; i++)
         {
            std::cout << i << " " << array[i].elem << "\n";
         }
      }
   }

   int size() const
   {
      return int(array.size()) - 1;
   }

   bool empty() const
   {
      return size() == 0;
   }

   Par const &top() const
   {
      if (size() == 0)
         throw std::domain_error("No se puede consultar el primero de una cola vacia");
      else
         return array[1];
   }

   void pop()
   {
      if (size() == 0)
         throw std::domain_error("No se puede eliminar el primero de una cola vacía.");
      else
      {
         posiciones.erase(array[1].elem); // para indicar que no está
         if (size() > 1)
         {
            array[1] = std::move(array.back());
            posiciones[array[1].elem] = 1;
            array.pop_back();
            hundir(1);
         }
         else
            array.pop_back();
      }
   }

   T const &priority(K e) const
   {
      if (posiciones.count(e) == 0)
         throw std::domain_error("No se puede consultar la prioridad de un elemento que no ha sido insertado aún.");
      int i = posiciones.at(e);
      return array[i].prioridad;
   }

   int count(K e) const
   {
      return posiciones.count(e);
   }

private:
   void flotar(int i)
   {
      Par parmov = std::move(array[i]);
      int hueco = i;
      while (hueco != 1 && antes(parmov.prioridad, array[hueco / 2].prioridad))
      {
         array[hueco] = std::move(array[hueco / 2]);
         posiciones[array[hueco].elem] = hueco;
         hueco /= 2;
      }
      array[hueco] = std::move(parmov);
      posiciones[array[hueco].elem] = hueco;
   }

   void hundir(int i)
   {
      Par parmov = std::move(array[i]);
      int hueco = i;
      int hijo = 2 * hueco; // hijo izquierdo, si existe
      while (hijo <= size())
      {
         // cambiar al hijo derecho de i si existe y va antes que el izquierdo
         if (hijo < size() && antes(array[hijo + 1].prioridad, array[hijo].prioridad))
            ++hijo;
         // flotar el hijo si va antes que el elemento hundiéndose
         if (antes(array[hijo].prioridad, parmov.prioridad))
         {
            array[hueco] = std::move(array[hijo]);
            posiciones[array[hueco].elem] = hueco;
            hueco = hijo;
            hijo = 2 * hueco;
         }
         else
            break;
      }
      array[hueco] = std::move(parmov);
      posiciones[array[hueco].elem] = hueco;
   }
};

#endif /* INDEXPQ_H_ */
