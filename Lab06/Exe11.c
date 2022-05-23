static int findbit(int low, int startscan, int pages, int memflags, int *len)
{
    int lenRun = 0,
        freeRangeStart = startscan,
        lenTotal = 0;

    printf("Initial position of the search: %d\n", startscan);
    printf("Limit position of the search: %d\n", low);
    printf("Number of pages needed: %d\n", pages);

    for (int i = startscan; i >= low; i--)
    {
        if (!page_isfree(i))
        {
            lenTotal++;
            int pi;
            int chunk = i / BITCHUNK_BITS, moved = 0;
            lenRun = 0;
            pi = i;
            while (chunk > 0 &&
                   !MAP_CHUNK(free_pages_bitmap, chunk * BITCHUNK_BITS))
            {
                chunk--;
                moved = 1;
            }
            if (moved)
            {
                i = chunk * BITCHUNK_BITS + BITCHUNK_BITS;
            }
            continue;
        }
        if (!lenRun)
        {
            freeRangeStart = i;
            lenRun = 1;
            lenTotal++;
        }
        else
        {
            freeRangeStart--;
            lenRun++;
            lenTotal++;
        }

        assert(lenRun <= pages);
        if (lenRun == pages)
        {
            *len = lenRun;

            printf("Position found: %d\n", freeRangeStart);
            printf("Restarts done before finding contiguous pages: %d\n", lenTotal - lenRun);
            printf("Bitmap: ");

            for (i = freeRangeStart; i <= freeRangeStart + pages; i++)
            {
                if (page_isfree(i))
                    printf("1");
                else
                    printf("0");
            }
            return freeRangeStart;
        }
    }
    return NO_MEM;
}