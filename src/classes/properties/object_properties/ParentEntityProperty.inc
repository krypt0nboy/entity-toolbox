<?php

/**
 * Class ParentEntityProperty
 */
class ParentEntityProperty extends EntityProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                   => 'parent',
        'default_reference'              => '%property_default_reference%',
        'default_name'                   => '%property_default_reference%',
        'default_label'                  => '%property_reference_info_labels_single%',
        'default_description'            => 'The %toolbox_info_entity_type% %property_reference_info_label% (parent).',
        'default_has_revisions'          => TRUE,
        'default_has_translations'       => FALSE,
        'default_key'                    => '%property_reference%',
        'default_schemas_fields_name'    => array(
          'base'              => 'parent_%property_reference_info_keys_id%',
          'revision'          => 'parent_%property_reference_info_keys_id%',
          'relation'          => 'parent_%property_reference_info_keys_id%',
          'relation_revision' => 'parent_%property_reference_info_keys_id%',
        ),
        'default_schemas_fields'         => array(
          'base'              => array(
            'description' => 'The {%property_reference_info_base_table%}.%property_reference_info_keys_id%.',
          ),
          'revision'          => array(
            'description' => 'The {%property_reference_info_base_table%}.%property_reference_info_keys_id% revision.',
          ),
        ),
        'default_forms'                  => array(
          'edit'   => array(
            'required' => TRUE,
          ),
          'inline' => array(
            'expose' => TRUE,
          ),
        ),
      ),
      $args
    );

    parent::__construct($args);
  }
}