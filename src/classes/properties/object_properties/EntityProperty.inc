<?php

/**
 * Class EntityProperty
 */
class EntityProperty extends ObjectProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'reference',
        'default_php_type'            => 'object',
        'default_drupal_type'         => '%reference_info_entity_type%',
        'default_reference'           => '%reference_info_entity_type%',
        'default_name'                => '%reference_info_entity_type%',
        'default_has_translations'    => FALSE,
        'default_key'                 => '%reference_info_entity_keys_id%',
        'default_schemas_fields_name' => array(
          'base'              => '%reference_info_entity_keys_id%',
          'revision'          => '%reference_info_entity_keys_id%',
          'relation'          => '%reference_info_entity_keys_id%',
          'relation_revision' => '%reference_info_entity_keys_id%',
        ),
        'default_schemas_fields'      => array(
          'base'              => array(
            'description' => 'The {%reference_info_base_table%}.%reference_info_entity_keys_id%',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
            'unsigned'    => FALSE,
          ),
          'revision'          => array(
            'description' => '',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
            'unsigned'    => FALSE,
          ),
          'relation'          => array(
            'description' => 'The {%reference_info_base_table%}.%reference_info_entity_keys_id%',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
            'unsigned'    => FALSE,
          ),
          'relation_revision' => array(
            'description' => 'The {%reference_info_base_table%}.%reference_info_entity_keys_id%',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
            'unsigned'    => FALSE,
          ),
        ),
        'default_forms'               => array(
          'edit'   => array(
            'expose'   => TRUE,
            'widget'   => 'select',
            'required' => FALSE,
          ),
          'clone'  => array(
            'expose'   => FALSE,
            'required' => FALSE,
          ),
          'inline' => array(
            'expose'   => TRUE,
            'widget'   => 'select',
            'required' => FALSE,
          ),
        ),
        'default_views_expose'        => TRUE,
        'default_value'               => array(
          'bundles' => array()
        ),
      ),
      $args
    );

    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function isPropertyReference() {
    return TRUE;
  }
}