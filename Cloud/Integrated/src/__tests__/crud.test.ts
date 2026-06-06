import {describe, expect, test} from 'vitest';
import prismaMock from '../singleton'

test('Sanity test of mock', async () => {
  prismaMock.profile.findFirst.mockResolvedValue(null);
  await expect(prismaMock.profile.findFirst({})).resolves.toBeNull()
})