.. -*- rst -*-
.. needs:method_verification
.. needs:parameter_verification
.. needs:example_verification
.. needs:body_verification

==========================
Floating IPs (floatingips)
==========================

List floating IPs
=================

.. rest_method::  GET /v2.0/floatingips

Lists floating IPs that are accessible to the tenant who submits the request.

Default policy settings return only those floating IPs that are
owned by the tenant who submits the request, unless an admin user
submits the request.

This example request lists floating IPs in JSON format:

::

   GET /v2.0/floatingips
   Accept: application/json

Use the ``fields`` query parameter to control which fields are
returned in the response body. Additionally, you can filter results
by using query string parameters. For information, see `Filtering
and Column Selection <https://wiki.openstack.org/wiki/Neutron/APIv2
-specification#Filtering_and_Column_Selection>`__.

Normal response codes: 200
Error response codes:401,

Request
-------

Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - status: status
   - tenant_id: tenant_id
   - floating_network_id: floating_network_id
   - fixed_ip_address: fixed_ip_address
   - floating_ip_address: floating_ip_address
   - port_id: port_id
   - id: id
   - floatingips: floatingips

Response Example
----------------

.. literalinclude:: samples/floatingips/floating-ips-list-response.json
   :language: javascript

Create floating IP
==================

.. rest_method::  POST /v2.0/floatingips

Creates a floating IP, and, if you specify port information, associates the floating IP with an internal port.

To associate the floating IP with an internal port, specify the
port UUID attribute in the request body. If you do not specify a
port UUID in the request, you can issue a PUT request instead of a
POST request.

Default policy settings enable only administrative users to set
floating IP addresses and some non-administrative users might
require a floating IP address. If you do not specify a floating IP
address in the request, the operation automatically allocates one.

By default, this operation associates the floating IP address with
a single fixed IP address that is configured on an OpenStack
Networking port. If a port has multiple IP addresses, you must
specify the ``fixed_ip_address`` attribute in the request body to
associate a fixed IP address with the floating IP address.

You can create floating IPs on only external networks. When you
create a floating IP, you must specify the UUID of the network on
which you want to create the floating IP. Alternatively, you can
create a floating IP on a subnet in the external network, based on
the costs and quality of that subnet.

You must configure an IP address with the internal OpenStack
Networking port that is associated with the floating IP address.

Error codes:

- ``400`` The operation returns this error code for one of these
  reasons:

  - The network is not external, such as ``router:external=False``.

  - The internal OpenStack Networking port is not associated with the
    floating IP address.

  - The requested floating IP address does not fall in the subnet
    range for the external network.

  - The fixed IP address is not valid.

- ``401`` The operation is not authorized.

- ``404`` The port UUID is not valid.

- ``409`` The operation returns this error code for one of these
  reasons:

  - The requested floating IP address is already in use.

  - The internal OpenStack Networking port and fixed IP address are
    already associated with another floating IP.

Error response codes:201,404,409,401,400,

Request
-------

.. rest_parameters:: parameters.yaml

   - floatingip: floatingip
   - tenant_id: tenant_id
   - floating_network_id: floating_network_id
   - fixed_ip_address: fixed_ip_address
   - floating_ip_address: floating_ip_address
   - port_id: port_id

Request Example
---------------

.. literalinclude:: samples/floatingips/floatingip-create-request.json
   :language: javascript

Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - status: status
   - floatingip: floatingip
   - tenant_id: tenant_id
   - floating_network_id: floating_network_id
   - fixed_ip_address: fixed_ip_address
   - floating_ip_address: floating_ip_address
   - port_id: port_id
   - id: id

Show floating IP details
========================

.. rest_method::  GET /v2.0/floatingips/{floatingip_id}

Shows details for a floating IP.

Use the ``fields`` query parameter to control which fields are
returned in the response body. For information, see `Filtering and
Column Selection <http://specs.openstack.org/openstack /neutron-
specs/specs/api/networking_general_api_information.html #filtering-
and-column-selection>`__.

This example request shows details for a floating IP in JSON
format. This example also filters the result by the
``fixed_ip_address`` and ``floating_ip_address`` fields.

::

   GET /v2.0/floatingips/{floatingip_id}?fields=fixed_ip_address
   &
   fields=floating_ip_address
   Accept: application/json

Normal response codes: 200
Error response codes:404,403,401,

Request
-------

.. rest_parameters:: parameters.yaml

   - floatingip_id: floatingip_id

Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - status: status
   - floatingip: floatingip
   - tenant_id: tenant_id
   - floating_network_id: floating_network_id
   - fixed_ip_address: fixed_ip_address
   - floating_ip_address: floating_ip_address
   - port_id: port_id
   - id: id

Response Example
----------------

.. literalinclude:: samples/floatingips/floatingip-show-response.json
   :language: javascript

Update floating IP
==================

.. rest_method::  PUT /v2.0/floatingips/{floatingip_id}

Updates a floating IP and its association with an internal port.

The association process is the same as the process for the create
floating IP operation.

To disassociate a floating IP from a port, set the ``port_id``
attribute to null or omit it from the request body.

This example updates a floating IP:

::

   PUT /v2.0/floatingips/{floatingip_id} Accept: application/json

Depending on the request body that you submit, this request
associates a port with or disassociates a port from a floating IP.

Normal response codes: 200
Error response codes:404,409,401,400,

Request
-------

.. rest_parameters:: parameters.yaml

   - port_id: port_id
   - floatingip: floatingip
   - floatingip_id: floatingip_id

Request Example
---------------

.. literalinclude:: samples/floatingips/floatingip-disassociate-request.json
   :language: javascript

Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - router_id: router_id
   - status: status
   - floatingip: floatingip
   - tenant_id: tenant_id
   - floating_network_id: floating_network_id
   - fixed_ip_address: fixed_ip_address
   - floating_ip_address: floating_ip_address
   - port_id: port_id
   - id: id

Response Example
----------------

.. literalinclude:: samples/floatingips/floatingip-disassociate-response.json
   :language: javascript

Delete floating IP
==================

.. rest_method::  DELETE /v2.0/floatingips/{floatingip_id}

Deletes a floating IP and, if present, its associated port.

This example deletes a floating IP:

::

   DELETE /v2.0/floatingips/{floatingip_id} Accept: application/json

Error response codes:404,204,401,

Request
-------

.. rest_parameters:: parameters.yaml

   - floatingip_id: floatingip_id
