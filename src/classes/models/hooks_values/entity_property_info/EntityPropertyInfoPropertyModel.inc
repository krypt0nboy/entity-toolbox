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
            'type'   => 'string',
            'method' => 'buildBundle',
          ),
          'options list'        => array(
            'type'   => 'string',
            'method' => 'buildOptionsList',
          ),
          'getter callback'     => array(
            'type'    => 'string',
            'default' => '%property_callbacks_getter%',
          ),
          'setter callback'     => array(
            'type'    => 'string',
            'default' => '%property_callbacks_setter%',
          ),
          'validation callback' => array(
            'type'    => 'string',
            'default' => '%property_callbacks_validation%',
          ),
          'access callback'     => array(
            'type'    => 'string',
            'default' => '%property_callbacks_access%',
          ),
          'setter permission'   => array(
            'type'    => 'string',
            'default' => '%property_setter_permission%',
          ),
          'schema field'        => array(
            'type'   => 'string',
            'method' => 'buildSchemaField',
          ),
          'required'            => array(
            'type'    => 'boolean',
            'default' => '%property_required%',
          ),
          'field'               => array(
            'type'   => 'string',
            'method' => 'buildField',
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
            'type'   => 'string',
            'method' => 'buildSanitize',
          ),
          'raw getter callback' => array(
            'type'   => 'string',
            'method' => 'buildRawGetterCallback',
          ),
          'clear'               => array(
            'type'   => 'array',
            'method' => 'buildClear',
          ),
          'property info'       => array(
            'type'   => 'array',
            'method' => 'buildPropertyInfo',
          ),
          'property info alter' => array(
            'type'   => 'array',
            'method' => 'buildPropertyInfoAlter',
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
            'model'  => 'property_token'
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}