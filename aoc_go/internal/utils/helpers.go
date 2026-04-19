package utils

func FoldL[T any, U any](slice []T, initial U, f func(U, T) U) U {
	acc := initial
	for _, v := range slice {
		acc = f(acc, v)
	}
	return acc
}

func FoldR[T any, U any](slice []T, initial U, f func(U, T) U) U {
	acc := initial
	for i := len(slice) - 1; i >= 0; i-- {
		acc = f(acc, slice[i])
	}
	return acc
}

func SliceCount[T comparable](slice []T, val T) int {
	var count int
	for _, v := range slice {
		if v == val {
			count++
		}
	}
	return count
}
