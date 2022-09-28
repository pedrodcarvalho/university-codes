template <typename T>
void mergeSort(std::vector<T> &data, int i, int k)
{
    int j;

    if (i < k) {
        j = (i + k) / 2;

        mergeSort(data, i, j);
        mergeSort(data, j + 1, k);

        int mergedSize, mergePos, leftPos, rightPos;
        std::vector<T> mergedData;

        mergePos = 0;
        mergedSize = k - i + 1;
        leftPos = i;
        rightPos = j + 1;
        mergedData = data;

        while (leftPos <= j && rightPos <= k) {
            if (data.at(leftPos) < data.at(rightPos)) {
                mergedData.at(mergePos) = data.at(leftPos);
                leftPos++;
            }
            else {
                mergedData.at(mergePos) = data.at(rightPos);
                rightPos++;
            }

            mergePos++;
        }

        while (leftPos <= j) {
            mergedData.at(mergePos) = data.at(leftPos);
            leftPos++;
            mergePos++;
        }

        while (rightPos <= k) {
            mergedData.at(mergePos) = data.at(rightPos);
            rightPos++;
            mergePos++;
        }

        for (mergePos = 0; mergePos < mergedSize; mergePos++) {
            data.at(i + mergePos) = mergedData.at(mergePos);
        }
    }
};
