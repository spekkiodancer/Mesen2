﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mesen.Utilities
{
	public static class SortHelper
	{
		public static void SortArray<T>(T[] array, List<Tuple<string, ListSortDirection>> sortOrder, Dictionary<string, Func<T, T, int>> comparers, string defaultColumnSort)
		{
			Func<T, T, int> defaultComparer = comparers[defaultColumnSort];
			switch(sortOrder.Count) {
				case 1: {
					Func<T, T, int> comparer = comparers[sortOrder[0].Item1];
					int order = sortOrder[0].Item2 == ListSortDirection.Ascending ? 1 : -1;
					Array.Sort(array, (a, b) => {
						int result = comparer(a, b);
						if(result != 0) {
							return result * order;
						}
						return defaultComparer(a, b);
					});
					return;
				}

				case 2: {
					Func<T, T, int> comparer = comparers[sortOrder[0].Item1];
					Func<T, T, int> comparer2 = comparers[sortOrder[1].Item1];
					int order = sortOrder[0].Item2 == ListSortDirection.Ascending ? 1 : -1;
					int order2 = sortOrder[1].Item2 == ListSortDirection.Ascending ? 1 : -1;
					Array.Sort(array, (a, b) => {
						int result;
						if((result = comparer(a, b)) != 0) {
							return result * order;
						} else if((result = comparer2(a, b)) != 0) {
							return result * order2;
						}
						return defaultComparer(a, b);
					});
					return;
				}

				case 3: {
					Func<T, T, int> comparer = comparers[sortOrder[0].Item1];
					Func<T, T, int> comparer2 = comparers[sortOrder[1].Item1];
					Func<T, T, int> comparer3 =  comparers[sortOrder[2].Item1];
					int order = sortOrder[0].Item2 == ListSortDirection.Ascending ? 1 : -1;
					int order2 = sortOrder[1].Item2 == ListSortDirection.Ascending ? 1 : -1;
					int order3 = sortOrder[2].Item2 == ListSortDirection.Ascending ? 1 : -1;
					Array.Sort(array, (a, b) => {
						int result;
						if((result = comparer(a, b)) != 0) {
							return result * order;
						} else if((result = comparer2(a, b)) != 0) {
							return result * order2;
						} else if((result = comparer3(a, b)) != 0) {
							return result * order3;
						}
						return defaultComparer(a, b);
					});
					return;
				}

				default:
					Array.Sort(array, (a, b) => {
						foreach((string column, ListSortDirection order) in sortOrder) {
							int result = comparers[column](a, b);
							if(result != 0) {
								return result * (order == ListSortDirection.Ascending ? 1 : -1);
							}
						}
						return defaultComparer(a, b);
					});
					return;
			}
		}
	}
}
