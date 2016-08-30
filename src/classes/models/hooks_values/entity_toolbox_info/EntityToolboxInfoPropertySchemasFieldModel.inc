<?php

/**
 * Class EntityToolboxInfoPropertySchemasField
 */
class EntityToolboxInfoPropertySchemasFieldModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'description' => array(
            'type'    => 'string',
            'default' => '%property_default_schemas_fields_base_description%',
          ),
          'type'        => array(
            'type'    => 'string',
            'default' => '%property_default_schemas_fields_base_type%',
          ),
          'serialize'   => array(
            'type'    => 'boolean',
            'default' => '%property_default_schemas_fields_base_serialize%',
          ),
          'size'        => array(
            'type'    => 'size',
            'default' => '%property_default_schemas_fields_base_size%',
          ),
          'not null'    => array(
            'type'    => 'boolean',
            'default' => '%property_default_schemas_fields_base_not_null%',
          ),
          'default'     => array(
            'type'    => 'mixed',
            'default' => '%property_default_schemas_fields_base_default%',
          ),
          'length'      => array(
            'type'    => 'integer',
            'default' => '%property_default_schemas_fields_base_length%',
          ),
          'unsigned'    => array(
            'type'    => 'boolean',
            'default' => '%property_default_schemas_fields_base_unsigned%',
          ),
          'precision'   => array(
            'type'    => 'integer',
            'default' => '%property_default_schemas_fields_base_precision%',
          ),
          'scale'       => array(
            'type'    => 'integer',
            'default' => '%property_default_schemas_fields_base_scale%',
          ),
          'binary'      => array(
            'type'    => 'boolean',
            'default' => '%property_default_schemas_fields_base_binary%',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}