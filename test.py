original_list = [1, 2, 3, 4, 5]

# Add three None elements before each element in the original list
result_list = [None] * 3 + [item for item in original_list for _ in range(1)]

print(result_list)