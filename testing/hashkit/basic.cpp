#include "../lib/common.hpp"

#include "libhashkit-1.0/hashkit.hpp"

static const char *input[] = {
    "apple",
    "beat",
    "carrot",
    "daikon",
    "eggplant",
    "flower",
    "green",
    "hide",
    "ick",
    "jack",
    "kick",
    "lime",
    "mushrooms",
    "nectarine",
    "orange",
    "peach",
    "quant",
    "ripen",
    "strawberry",
    "tang",
    "up",
    "volumne",
    "when",
    "yellow",
    "zip",
};

static const uint32_t output[][sizeof(input)/sizeof(*input)] = {
          // one_at_a_time
          { 2297466611U, 3902465932U, 469785835U, 1937308741U,
          261917617U, 3785641677U, 1439605128U, 1649152283U,
          1493851484U, 1246520657U, 2221159044U, 1973511823U,
          384136800U, 214358653U, 2379473940U, 4269788650U,
          2864377005U, 2638630052U, 427683330U, 990491717U,
          1747111141U, 792127364U, 2599214128U, 2553037199U,
          2509838425U },

          // md5
          { 3195025439U, 2556848621U, 3724893440U, 3332385401U,
          245758794U, 2550894432U, 121710495U, 3053817768U,
          1250994555U, 1862072655U, 2631955953U, 2951528551U,
          1451250070U, 2820856945U, 2060845566U, 3646985608U,
          2138080750U, 217675895U, 2230934345U, 1234361223U,
          3968582726U, 2455685270U, 1293568479U, 199067604U,
          2042482093U },

          // crc
          { 10542U, 22009U, 14526U, 19510U, 19432U, 10199U, 20634U,
          9369U, 11511U, 10362U, 7893U, 31289U, 11313U, 9354U,
          7621U, 30628U, 15218U, 25967U, 2695U, 9380U,
          17300U, 28156U, 9192U, 20484U, 16925U },

          // fnv1_64
          { 473199127U, 4148981457U, 3971873300U, 3257986707U,
          1722477987U, 2991193800U, 4147007314U, 3633179701U,
          1805162104U, 3503289120U, 3395702895U, 3325073042U,
          2345265314U, 3340346032U, 2722964135U, 1173398992U,
          2815549194U, 2562818319U, 224996066U, 2680194749U,
          3035305390U, 246890365U, 2395624193U, 4145193337U,
          1801941682U },

          // fnv1a_64
          { 1488911807U, 2500855813U, 1510099634U, 1390325195U,
          3647689787U, 3241528582U, 1669328060U, 2604311949U,
          734810122U, 1516407546U, 560948863U, 1767346780U,
          561034892U, 4156330026U, 3716417003U, 3475297030U,
          1518272172U, 227211583U, 3938128828U, 126112909U,
          3043416448U, 3131561933U, 1328739897U, 2455664041U,
          2272238452U },

          // fnv1_32
          { 67176023U, 1190179409U, 2043204404U, 3221866419U,
          2567703427U, 3787535528U, 4147287986U, 3500475733U,
          344481048U, 3865235296U, 2181839183U, 119581266U,
          510234242U, 4248244304U, 1362796839U, 103389328U,
          1449620010U, 182962511U, 3554262370U, 3206747549U,
          1551306158U, 4127558461U, 1889140833U, 2774173721U,
          1180552018U },

          // fnv1a_32
          { 280767167U, 2421315013U, 3072375666U, 855001899U,
          459261019U, 3521085446U, 18738364U, 1625305005U,
          2162232970U, 777243802U, 3323728671U, 132336572U,
          3654473228U, 260679466U, 1169454059U, 2698319462U,
          1062177260U, 235516991U, 2218399068U, 405302637U,
          1128467232U, 3579622413U, 2138539289U, 96429129U,
          2877453236U },

          // hsieh
#ifdef HAVE_HSIEH_HASH
          { 3738850110U, 3636226060U, 3821074029U, 3489929160U, 3485772682U, 80540287U,
          1805464076U, 1895033657U, 409795758U, 979934958U, 3634096985U, 1284445480U,
          2265380744U, 707972988U, 353823508U, 1549198350U, 1327930172U, 9304163U,
          4220749037U, 2493964934U, 2777873870U, 2057831732U, 1510213931U, 2027828987U,
          3395453351U },
#else
          {  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
#endif

          // murmur
#ifdef HAVE_MURMUR_HASH
          // murmur
          { 4142305122U, 734504955U, 3802834688U, 4076891445U,
          387802650U, 560515427U, 3274673488U, 3150339524U,
          1527441970U, 2728642900U, 3613992239U, 2938419259U,
          2321988328U, 1145154116U, 4038540960U, 2224541613U,
          264013145U, 3995512858U, 2400956718U, 2346666219U,
          926327338U, 442757446U, 1770805201U, 560483147U,
          3902279934U },
          // murmur3
          { 1120212521U, 1448785489U, 4186307405U, 2686268514U,
          444808887U, 221750260U, 3074673162U, 1946933257U,
          2826416675U, 2430719166U, 3200429559U, 297894347U,
          732888124U, 4050076964U, 3298336176U, 1336207361U,
          810553576U, 3748182674U, 3860119212U, 3439537197U,
          3044240981U, 1464271804U, 3896193724U, 2915115798U,
          1702843840U },
#else
          { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
          { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
#endif

          // jenkins
          { 1442444624U, 4253821186U, 1885058256U, 2120131735U,
          3261968576U, 3515188778U, 4232909173U, 4288625128U,
          1812047395U, 3689182164U, 2502979932U, 1214050606U,
          2415988847U, 1494268927U, 1025545760U, 3920481083U,
          4153263658U, 3824871822U, 3072759809U, 798622255U,
          3065432577U, 1453328165U, 2691550971U, 3408888387U,
          2629893356U }
};

TEST_CASE("hashkit") {
  hashkit_st st, *hp = hashkit_create(nullptr);
  Hashkit stack;
  Hashkit *heap = new Hashkit;

  REQUIRE(hashkit_create(&st));
  REQUIRE(hp);

  SECTION("can copy") {
    Hashkit stack_copy(stack);
    Hashkit *heap_copy(heap);
    hashkit_st st_copy, *st_ptr;

    (void) stack_copy;
    (void) heap_copy;

    st_ptr = hashkit_clone(&st_copy, &st);
    REQUIRE(st_ptr == &st_copy);
    REQUIRE(hashkit_compare(st_ptr, &st_copy));

    SUCCEED("OK");
  }

  SECTION("can assign") {
    Hashkit stack_copy;

    stack_copy = stack;
    (void) stack_copy;

    SUCCEED("OK");
  }

  SECTION("can digest default") {
    REQUIRE(2297466611U == stack.digest(S("apple")));
    REQUIRE(2297466611U == hashkit_digest(&st, S("apple")));
  }

  SECTION("can set hash function") {
    for (int f = HASHKIT_HASH_DEFAULT; f < HASHKIT_HASH_MAX; ++f) {
      auto h = static_cast<hashkit_hash_algorithm_t>(f);

      if (h == HASHKIT_HASH_CUSTOM) {
        continue;
      }
      if (!libhashkit_has_algorithm(h)) {
        WARN("hashkit algorithm not enabled: " << libhashkit_string_hash(h) << " (" << f << ")");
        continue;
      }

      REQUIRE(HASHKIT_SUCCESS == stack.set_function(h));
      REQUIRE(HASHKIT_SUCCESS == hashkit_set_function(&st, h));

      SECTION("can digest set hash function") {
        auto n = 0;

        for (auto i : input) {
          CHECK(output[f][n] == stack.digest(S(i)));
          CHECK(output[f][n] == hashkit_digest(&st, S(i)));
          CHECK(output[f][n] == libhashkit_digest(S(i), h));
          ++n;
        }
      }
    }
  }

  SECTION("is comparable") {
    REQUIRE(*heap == stack);
    REQUIRE(hashkit_compare(&st, hp));

    stack.set_function(HASHKIT_HASH_MD5);
    hashkit_set_function(&st, HASHKIT_HASH_MD5);

    REQUIRE_FALSE(*heap == stack);
    REQUIRE_FALSE(hashkit_compare(&st, hp));
  }

  delete heap;
  hashkit_free(&st);
  hashkit_free(hp);
}
