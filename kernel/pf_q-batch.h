/***************************************************************
 *                                                
 * (C) 2011-12 Nicola Bonelli <nicola.bonelli@cnit.it>   
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 ****************************************************************/


#ifndef _PF_Q_BATCH_H_
#define _PF_Q_BATCH_H_ 


#define PFQ_BATCH_MAX_LEN  1024


struct pfq_queue_skb
{
    struct sk_buff *queue[PFQ_BATCH_MAX_LEN];  /* sk_buff */
    size_t counter;
};


#define queue_for_each(skb, n, q) \
	for(n = 0; (n != (q)->counter) && (skb = (q)->queue[n]); \
        __builtin_prefetch((q)->queue[n+1], 0, 1), n++)

#define queue_for_each_backward(skb, n, q) \
	for(n = (q)->counter-1; (n >= 0) && (skb = (q)->queue[n]); \
        __builtin_prefetch((q)->queue[n-1], 0, 1), n--)


static inline
int
pfq_queue_skb_push(struct pfq_queue_skb *q, struct sk_buff *skb)
{
	 if (q->counter < (PFQ_BATCH_MAX_LEN-1))
	 {
     	q->queue[q->counter++] = skb;
        return 0; 
	 }
	 return -1;
}


static inline
void
pfq_queue_skb_flush(struct pfq_queue_skb *q)
{
 	q->counter = 0;
}

static inline
int
pfq_queue_skb_size(struct pfq_queue_skb *q)
{
	return q->counter;
}


#endif /* _PF_Q_BATCH_H_ */
