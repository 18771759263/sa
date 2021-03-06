#ifndef CZYALGORITHM_H
#define CZYALGORITHM_H

#include <czy.h>
#include <algorithm>

namespace czy{

///
/// \brief 把索引范围之外的内容拷贝
/// \param input_begin 容器起始迭代器
/// \param input_end 容器终止迭代器
/// \param index_begin 索引的起始迭代器
/// \param index_end 索引的终止迭代器
/// \param output_begin 结果的起始迭代器
/// \note 需要保证index_begin到index_end时有序的，如果无序，请先进行sort:
/// \code
/// std::sort(index_begin,index_end);
/// \endcode
///
template<typename _IT,typename _IT_Index,typename _IT_RES>
void copy_out_of_indexs(_IT input_begin,_IT input_end,_IT_Index index_begin,_IT_Index index_end
                        ,_IT_RES output_begin,size_t inputIndexStart = 0)
{
    if(index_begin == index_end)
    {
        std::copy(input_begin,input_end,output_begin);
        return;
    }
    while (input_begin!=input_end)
    {
      if (inputIndexStart == *index_begin)
      {
          ++input_begin;
          ++index_begin;
          ++inputIndexStart;
          if(index_begin == index_end)
          {
              break;
          }
          continue;
      }
      *output_begin = *input_begin;
      ++output_begin;
      ++inputIndexStart;
      ++input_begin;
    }
    std::copy(input_begin,input_end,output_begin);
}
///
/// \brief 把索引范围之内的内容拷贝
/// \param input_begin 容器起始迭代器
/// \param input_end 容器终止迭代器
/// \param index_begin 索引的起始迭代器
/// \param index_end 索引的终止迭代器
/// \param output_begin 结果的起始迭代器
/// \note 需要保证index_begin到index_end时有序的，如果无序，请先进行sort:
/// \code
/// std::sort(index_begin,index_end);
/// \endcode
///
template<typename _IT,typename _IT_Index,typename _IT_RES>
void copy_inner_indexs(_IT input_begin,_IT input_end,_IT_Index index_begin,_IT_Index index_end
                        ,_IT_RES output_begin,size_t inputIndexStart = 0)
{
    if(index_begin == index_end)
    {
        return;
    }
    while (input_begin!=input_end)
    {
        if (inputIndexStart == *index_begin)
        {
            *output_begin = *input_begin;
            ++output_begin;
            ++index_begin;
            if(index_begin == index_end)
            {
                return;
            }
        }
        ++inputIndexStart;
        ++input_begin;
    }
}


///
/// \brief 根据提供的索引把一个序列分解为两个结集
///  ，其中 outputInnerIndex_begin存放在提供范围内的结果
///  outputOutOfIndex_begin存放提供的索引范围外的结果
/// \param input_begin 容器起始迭代器
/// \param input_end 容器终止迭代器
/// \param index_begin 索引的起始迭代器
/// \param index_end 索引的终止迭代器
/// \param outputInnerIndex_begin 存放在提供索引范围内的结果
/// \param outputOutOfIndex_begin 存放提供的索引范围外的结果
/// \note 需要保证index_begin到index_end时有序的，如果无序，请先进行sort:
/// \code
/// std::sort(index_begin,index_end);
/// \endcode
///
template<typename _IT,typename _IT_Index,typename _IT_RES>
void split_with_indexs(_IT input_begin,_IT input_end,_IT_Index index_begin,_IT_Index index_end
                       ,_IT_RES outputInnerIndex_begin,_IT_RES outputOutOfIndex_begin
                       ,size_t inputIndexStart = 0)
{
    if(index_begin == index_end)
    {
        std::copy(input_begin,input_end,outputOutOfIndex_begin);
        return;
    }
    while (input_begin != input_end)
    {
      if (inputIndexStart == (size_t)(*index_begin))
      {
          *outputInnerIndex_begin = *input_begin;
          ++outputInnerIndex_begin;
          ++index_begin;
          if(index_begin == index_end)
          {
              ++input_begin;
              break;
          }
      }
      else
      {
          *outputOutOfIndex_begin = *input_begin;
          ++outputOutOfIndex_begin;
      }
      ++inputIndexStart;
      ++input_begin;
    }
    std::copy(input_begin,input_end,outputOutOfIndex_begin);
}


///
/// \brief transform 3参数的transform，对std::transform的扩展，适用于3参数
/// \param first1 参数1的开始迭代器
/// \param last1 参数1的结束迭代器
/// \param first2 参数2的开始迭代器
/// \param first3 参数3的开始迭代器
/// \param result 结果的迭代器
/// \param three_op 函数指针，此函数指针形式为result = fun(arg1,arg2,arg3)
/// \return 返回结果迭代器最后的指向
///
template <class InputIterator1, class InputIterator2, class InputIterator3
          ,class OutputIterator
          , class ThreeOperation>
OutputIterator transform (InputIterator1 first1, InputIterator1 last1
                           ,InputIterator2 first2,InputIterator3 first3
                           ,OutputIterator result_first,
                           ThreeOperation three_op)
{
    while (first1 != last1) {
        *result_first = three_op(*first1,*first2,*first3);  // or: *result=binary_op(*first1,*first2++);
        ++result_first;
        ++first1;++first2;++first3;
    }
    return result_first;
}
///
/// \brief transform 4参数的transform，对std::transform的扩展，适用于4参数
/// \param first1 参数1的开始迭代器
/// \param last1 参数1的结束迭代器
/// \param first2 参数2的开始迭代器
/// \param first3 参数3的开始迭代器
/// \param first4 参数4的开始迭代器
/// \param result 结果的迭代器
/// \param four_op 函数指针，此函数指针形式为result = fun(arg1,arg2,arg3,arg4)
/// \return 返回结果迭代器最后的指向
///
template <class InputIterator1, class InputIterator2, class InputIterator3, class InputIterator4
          ,class OutputIterator
          , class FourOperation>
OutputIterator transform (InputIterator1 first1, InputIterator1 last1
                           ,InputIterator2 first2,InputIterator3 first3,InputIterator4 first4
                           ,OutputIterator result_first,
                           FourOperation four_op)
{
    while (first1 != last1) {
        *result_first = four_op(*first1,*first2,*first3,*first4);  // or: *result=binary_op(*first1,*first2++);
        ++result_first;
        ++first1;++first2;++first3;++first4;
    }
    return result_first;
}
///
/// \brief transform 4参数的transform，对std::transform的扩展，适用于5参数
/// \param first1 参数1的开始迭代器
/// \param last1 参数1的结束迭代器
/// \param first2 参数2的开始迭代器
/// \param first3 参数3的开始迭代器
/// \param first4 参数4的开始迭代器
/// \param first5 参数5的开始迭代器
/// \param result 结果的迭代器
/// \param five_op 函数指针，此函数指针形式为result = fun(arg1,arg2,arg3,arg4,arg5)
/// \return 返回结果迭代器最后的指向
///
template <class InputIterator1, class InputIterator2, class InputIterator3, class InputIterator4, class InputIterator5
          ,class OutputIterator
          , class FiveOperation>
OutputIterator transform (InputIterator1 first1, InputIterator1 last1
                           ,InputIterator2 first2,InputIterator3 first3,InputIterator4 first4,InputIterator5 first5
                           ,OutputIterator result_first,
                           FiveOperation five_op)
{
    while (first1 != last1) {
        *result_first = five_op(*first1,*first2,*first3,*first4,*first5);  // or: *result=binary_op(*first1,*first2++);
        ++result_first;
        ++first1;++first2;++first3;++first4;++first5;
    }
    return result_first;
}

///
/// \brief transform 4参数的transform，对std::transform的扩展，适用于5参数
/// \param first1 参数1的开始迭代器
/// \param last1 参数1的结束迭代器
/// \param first2 参数2的开始迭代器
/// \param first3 参数3的开始迭代器
/// \param first4 参数4的开始迭代器
/// \param first5 参数5的开始迭代器
/// \param first6 参数6的开始迭代器
/// \param result 结果的迭代器
/// \param six_op 函数指针，此函数指针形式为result = fun(arg1,arg2,arg3,arg4,arg5,arg6)
/// \return 返回结果迭代器最后的指向
///
template <class InputIterator1, class InputIterator2, class InputIterator3, class InputIterator4, class InputIterator5, class InputIterator6
          ,class OutputIterator
          , class SixOperation>
OutputIterator transform (InputIterator1 first1, InputIterator1 last1
                           ,InputIterator2 first2,InputIterator3 first3,InputIterator4 first4,InputIterator5 first5,InputIterator6 first6
                           ,OutputIterator result_first,
                           SixOperation six_op)
{
    while (first1 != last1) {
        *result_first = six_op(*first1,*first2,*first3,*first4,*first5,*first6);  // or: *result=binary_op(*first1,*first2++);
        ++result_first;
        ++first1;++first2;++first3;++first4;++first5;++first6;
    }
    return result_first;
}

}

#endif // CZYALGORITHM_H
