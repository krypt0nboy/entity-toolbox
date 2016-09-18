<?php

/**
 * Class EntityPropertyInfoPropertyModel
 */
class EntityPropertyInfoPropertyModel extends EntityPropertyInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'label'               => array(
            'type'    => 'string',
            'default' => '%property_label%',
          ),
          'description'         => array(
            'type'    => 'string',
            'default' => '%property_description%',
          ),
          'type'                => array(
            'type'    => 'string',
            'default' => '%property_drupal_type%',
          ),
          'bundle'              => array(
            'type'     => 'string',
            'method'   => 'buildBundle',
            'unset if' => 'is_null:c:'
          ),
          'options list'        => array(
            'type'     => 'string',
            'method'   => 'buildOptionsList',
            'unset if' => 'is_null:c:'
          ),
          'getter callback'     => array(
            'type'     => 'string',
            'default'  => '%property_callbacks_getter%',
            'unset if' => 'is_null:c:'
          ),
          'setter callback'     => array(
            'type'     => 'string',
            'default'  => '%property_callbacks_setter%',
            'unset if' => 'is_null:c:'
          ),
          'validation callback' => array(
            'type'     => 'string',
            'default'  => '%property_callbacks_validation%',
            'unset if' => 'is_null:c:'
          ),
          'access callback'     => array(
            'type'     => 'string',
            'default'  => '%property_callbacks_access%',
            'unset if' => 'is_null:c:'
          ),
          'setter permission'   => array(
            'type'     => 'string',
            'default'  => '%property_setter_permission%',
            'unset if' => 'is_null:c:'
          ),
          'schema field'        => array(
            'type'     => 'string',
            'method'   => 'buildSchemaField',
            'unset if' => 'is_null:c:'
          ),
          'required'            => array(
            'type'    => 'boolean',
            'default' => '%property_required%',
          ),
          'field'               => array(
            'type'     => 'string',
            'method'   => 'buildField',
            'unset if' => 'is_null:c:'
          ),
          'computed'            => array(
            'type'   => 'boolean',
            'method' => 'buildComputed',
          ),
          'entity views field'  => array(
            'type'    => 'boolean',
            'default' => '%property_views_expose%',
          ),
          'sanitize'            => array(
            'type'     => 'string',
            'method'   => 'buildSanitize',
            'unset if' => 'is_null:c:'
          ),
          'raw getter callback' => array(
            'type'     => 'string',
            'method'   => 'buildRawGetterCallback',
            'unset if' => 'is_null:c:'
          ),
          'clear'               => array(
            'type'     => 'array',
            'method'   => 'buildClear',
            'unset if' => 'is_empty:c:'
          ),
          'property info'       => array(
            'type'     => 'array',
            'method'   => 'buildPropertyInfo',
            'unset if' => 'is_empty:c:'
          ),
          'property info alter' => array(
            'type'     => 'array',
            'method'   => 'buildPropertyInfoAlter',
            'unset if' => 'is_empty:c:'
          ),
          'auto creation'       => array(
            'type'   => 'boolean',
            'method' => 'buildAutoCreation',
          ),
          'translatable'        => array(
            'type'    => 'boolean',
            'default' => '%property_has_translations%',
          ),
          'entity token'        => array(
            'type'   => 'string',
            'method' => 'buildToken',
            'unset if' => 'is_null:c:'
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}