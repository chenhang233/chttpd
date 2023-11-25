#include <stdio.h>
#include <stdlib.h>
#include <netlink/socket.h>
#include <netlink/genl/ctrl.h>
#include <linux/nl80211.h>
#include <netlink/netlink.h>
#include <netlink/attr.h>

int main()
{
    struct nl_sock *sock = nl_socket_alloc();
    struct nl_msg *msg;
    struct nlattr *nl_attr;
    struct nlattr *nl_head;
    int rem = nla_len;
    int genl_family = genl_ctrl_resolve(sock, "nl80211");
    struct nla_policy info_policy[NL80211_ATTR_MAX + 1];
    memset(info_policy, 0, sizeof(info_policy));
    info_policy[NL80211_ATTR_IFINDEX].type = NLA_U32;
    info_policy[NL80211_ATTR_SSID].type = NLA_BINARY;
    info_policy[NL80211_ATTR_WIPHY].type = NLA_U32;
    genl_parse_family_attrs(genl_family, info_policy);
    msg = nlmsg_alloc();
    genlmsg_put(msg, NL_AUTO_PORT, NL_AUTO_SEQ, genl_family, 0, 0, NL80211_CMD_GET_INTERFACE, "wlan");
    nla_put(msg, NL80211_ATTR_IFINDEX, sizeof(int), &sock);
    nl_attr = nla_nest_start(msg, NL80211_ATTR_INTERFACE_COMBINATIONS);
    nla_nest_end(msg, nl_attr);
    if (genlmsg_send(sock, msg) < 0)
    {
        printf("Failed to send message\n");
        return -1;
    }
    char *buffer;
    size_t len;
    // 单播发送
    int ret = genlmsg_unicast(sock, msg, 0);
    if (ret < 0)
    {
        printf("Failed to send message\n");
        return -1;
    }

    // nla_for_each_attr(nl_attr, nl_head, rem)
    // {

    // }
    // nla_for_each_attr(nla, msg, nl_attr)
    // {
    //     if (nla->nla_type == NL80211_ATTR_IFINDEX)
    //     {
    //         printf("Interface index: %d\n", nla_get_u32(nla));
    //     }
    //     else if (nla->nla_type == NL80211_ATTR_SSID)
    //     {
    //         buffer = (char *)nla_data(nla);
    //         len = nla_len(nla);
    //         printf("SSID: %s\n", buffer);
    //     }
    //     else if (nla->nla_type == NL80211_ATTR_WIPHY)
    //     {
    //         printf("Wireless PHY index: %d\n", nla_get_u32(nla));
    //     }
    // }
    nlmsg_free(msg);
    nl_socket_free(sock);
    return 0;
}