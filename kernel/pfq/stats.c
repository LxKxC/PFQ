/***************************************************************
 *
 * (C) 2011-16 Nicola Bonelli <nicola@pfq.io>
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

#include <pfq/kcompat.h>
#include <pfq/stats.h>


void pfq_kernel_stats_read(struct pfq_kernel_stats __percpu *kstats, struct pfq_stats *stats)
{
	stats->recv = (long unsigned)sparse_read(kstats, recv);
	stats->lost = (long unsigned)sparse_read(kstats, lost);
	stats->drop = (long unsigned)sparse_read(kstats, drop);

	stats->sent = (long unsigned)sparse_read(kstats, sent);
	stats->disc = (long unsigned)sparse_read(kstats, disc);
	stats->fail = (long unsigned)sparse_read(kstats, fail);

	stats->frwd = (long unsigned)sparse_read(kstats, frwd);
	stats->kern = (long unsigned)sparse_read(kstats, kern);
}


void pfq_kernel_stats_reset(struct pfq_kernel_stats __percpu *stats)
{
	int i;
	for_each_present_cpu(i)
	{
		struct pfq_kernel_stats * stat = per_cpu_ptr(stats, i);

		local_set(&stat->recv, 0);
		local_set(&stat->lost, 0);
		local_set(&stat->drop, 0);
		local_set(&stat->sent, 0);
		local_set(&stat->disc, 0);
		local_set(&stat->fail, 0);
		local_set(&stat->frwd, 0);
		local_set(&stat->kern, 0);
	}
}

void pfq_group_counters_reset(struct pfq_group_counters __percpu *counters)
{
	int i, n;
	for_each_present_cpu(i)
	{
		struct pfq_group_counters * ctr = per_cpu_ptr(counters, i);
		for(n = 0; n < Q_MAX_COUNTERS; n++)
			local_set(&ctr->value[n], 0);
	}
}


void pfq_memory_stats_reset(struct pfq_memory_stats __percpu *stats)
{
	int i;
	for_each_present_cpu(i)
	{
		struct pfq_memory_stats * stat = per_cpu_ptr(stats, i);

		local_set(&stat->os_alloc,   0);
		local_set(&stat->os_free,    0);

		local_set(&stat->pool_pop[0],   0);
		local_set(&stat->pool_pop[1],   0);

		local_set(&stat->pool_push[0],  0);
		local_set(&stat->pool_push[1],  0);

		local_set(&stat->pool_empty[0],  0);
		local_set(&stat->pool_empty[1],  0);

		local_set(&stat->pool_norecycl[0],  0);
		local_set(&stat->pool_norecycl[1],  0);

		local_set(&stat->err_shared, 0);
		local_set(&stat->err_cloned, 0);
		local_set(&stat->err_memory, 0);
		local_set(&stat->err_irqdis, 0);
		local_set(&stat->err_fclone, 0);
		local_set(&stat->err_nolinr, 0);
		local_set(&stat->err_nfound, 0);
		local_set(&stat->err_broken, 0);

		local_set(&stat->dbg_dst_drop, 0);
		local_set(&stat->dbg_skb_dtor, 0);
		local_set(&stat->dbg_skb_frag_unref, 0);
		local_set(&stat->dbg_skb_free_frag, 0);
		local_set(&stat->dbg_skb_free_head, 0);
	}
}

