<?php

/**
 * Class EntityProperty
 */
class EntityProperty extends ObjectProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                   => 'reference',
        'default_php_type'               => 'object',
        'default_drupal_type'            => 'entity',
        'default_reference'              => '%property_default_drupal_type%',
        'default_name'                   => '%property_default_reference%',
        'default_has_translations'       => FALSE,
        'default_key'                    => '%property_reference_info_entity_keys_id%',
        'default_schemas_fields_name'    => array(
          'base'              => '%property_reference_info_entity_keys_id%',
          'revision'          => '%property_reference_info_entity_keys_id%',
          'relation'          => '%property_reference_info_entity_keys_id%',
          'relation_revision' => '%property_reference_info_entity_keys_id%',
        ),
        'default_schemas_fields'         => array(
          'base'              => array(
            'description' => 'The {%property_reference_info_base_table%}.%property_reference_info_entity_keys_id%',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
          ),
          'revision'          => array(
            'description' => '',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
          ),
          'relation'          => array(
            'description' => 'The {%property_reference_info_base_table%}.%property_reference_info_keys_id%',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
          ),
          'relation_revision' => array(
            'description' => '',
            'type'        => 'int',
            'not null'    => TRUE,
            'default'     => 0,
          ),
        ),
        'default_forms'                  => array(
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
        'default_views_expose'           => TRUE,
        'default_value'                  => array(
          'bundles' => array()
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}