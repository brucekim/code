int solution(int N)
{
    int cnt = 0;
    int max = 0;
    int i = 0;
    int j = 0;
    for (i = 0; i < 31; ++i)
    {
        if (N & (1 << i))
        {
            cnt = 0;
            for (j = i + 1; j < 32; ++j)
            {
                if (N & (1 << j))
                {
                    if (max < cnt)
                        max = cnt;
                    i = j - 1;
                    break;
                }
                else
                {
                    ++cnt;
                }
            }
            if (j == 32)
                break;
        }
    }
    return max;
}
